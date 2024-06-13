"use client"

import Image from "next/image"
import { useState } from "react"

function Square({ value, onSquareClick }) {
  return (
    <button
      className="btn"
      onClick={onSquareClick}
    >
      {value}
    </button>
  )
}
function Board({ count, squares, onPlay }) {

  function handleClick(idx) {
    const nextSquares = squares.slice()
    nextSquares[idx] = count
    onPlay(nextSquares)
  }

  return (
    <>
      <div className="board-row">
        <Square value={squares[0]} onSquareClick={() => handleClick(0)} />
        <Square value={squares[1]} onSquareClick={() => handleClick(1)} />
        <Square value={squares[2]} onSquareClick={() => handleClick(2)} />
      </div>
      <div className="board-row">
        <Square value={squares[3]} onSquareClick={() => handleClick(3)} />
        <Square value={squares[4]} onSquareClick={() => handleClick(4)} />
        <Square value={squares[5]} onSquareClick={() => handleClick(5)} />
      </div>
      <div className="board-row">
        <Square value={squares[6]} onSquareClick={() => handleClick(6)} />
        <Square value={squares[7]} onSquareClick={() => handleClick(7)} />
        <Square value={squares[8]} onSquareClick={() => handleClick(8)} />
      </div>
    </>
  );
}

function Game() {
  const [history, setHistory] = useState([Array(9).fill('Z')]);
  const [count, setCount] = useState(0)
  const [currentMove, setCurrentMove] = useState(0);

  // With setCurrentMove currentSquares is rendered properly.
  const currentSquares = history[currentMove];


  function jumpTo(nextMove) {
    setCurrentMove(nextMove);

    // Although there is a currentMove in handlePlay, 
    // it is not rendered with this setHistory.
    setHistory(history.slice(0, nextMove + 1));
  }

  function handlePlay(nextSquares) {
    // setHistory([...history, nextSquares]);
    const nextHistory = [...history.slice(0, currentMove + 1), nextSquares];
    setCount(count + 1)
    setHistory(nextHistory);
    setCurrentMove(nextHistory.length - 1);
  }

  // With proper use of the map method, 
  // the history array is converted to a moves array.
  const moves = history.map((squares, move) => {
    const description = move > 0 ? 'Go to move #' + move : 'Go to game start'

    // It is strongly recommended that 
    // you assign an appropriate key 
    // whenever you create a dynamic list.
    return (
      <li key={move}>
        <button onClick={() => jumpTo(move)}>{description}</button>
      </li>
    )
  })

  return (
    <div className="game">
      <div className="game-board">
        <Board
          count={count}
          squares={currentSquares}
          onPlay={handlePlay}
        />
        {history[history.length - 1]}
      </div>
      <div className="game-info">
        <ol>
          {moves}
        </ol>
      </div>
    </div>
  );
}

export default function Home() {
  return (
    <main className="flex min-h-screen flex-col items-center justify-between p-24">
      <Game />
    </main>
  )
}
