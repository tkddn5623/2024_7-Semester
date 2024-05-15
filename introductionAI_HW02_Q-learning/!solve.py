from __future__ import absolute_import
from src.maze_manager import MazeManager


if __name__ == '__main__':
    for i in range(3):
        manager = MazeManager()

        maze = manager.add_maze(20, 20)

        qtable = [[[0 for k in range(4)] for j in range(maze.num_cols)] for i in range(maze.num_rows)]

        manager.q_learning(maze.id, 50, 0.6, 0.6, 0.4, qtable=qtable)
        manager.q_learning_path(maze.id, 0.6, 0.6, 0.4, qtable=qtable)

        manager.show_solution_animation(maze.id)
