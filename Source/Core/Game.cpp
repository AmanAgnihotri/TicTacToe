#include "Core/Game.h"

Game::Game()
{
  currentMark = Mark::X;
}

Mark Game::getCurrentMark()
{
  return currentMark;
}

GameEvent Game::apply(int rank, int file)
{
  const auto applied = board.apply(rank, file, currentMark);
  
  if (!applied)
  {
    return GameEvent::AlreadyOccupied;
  }
  
  switch (board.getState())
  {
    case State::Playable:
      currentMark = (currentMark == Mark::X) ? Mark::O : Mark::X;
      
      return GameEvent::Applied;
      
    case State::Win:
      return (currentMark == Mark::X) ? GameEvent::WinForX : GameEvent::WinForO;
      
    default:
      return GameEvent::Draw;
  }
}
