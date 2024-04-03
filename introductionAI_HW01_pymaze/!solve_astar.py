from __future__ import absolute_import
from src.maze_manager import MazeManager


if __name__ == '__main__':

    # Create the manager
    manager = MazeManager()

    # Add a 10x10 maze to the manager
    maze = manager.add_maze(20, 20)

    # Solve the maze using the Depth First Backtracker algorithm
    manager.solve_maze(maze.id, 'AStar', 'brute-force')

    # Show how the maze was solved
    # If you want to save the animation, uncomment below
    # manager.set_filename('solution_anime_astar')
    manager.show_solution_animation(maze.id)
