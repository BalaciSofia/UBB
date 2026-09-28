import json
from domain import Info


class Repository:
    def __init__(self, filename="game_state.json"):
        """Initialize repository with a JSON file for persistence."""
        self.__filename = filename

    def save_game_state(self, info: Info, year: int) -> None:
        """Save the current game state to a JSON file."""
        game_data = {
            "year": year,
            "starved": info.starved,
            "immigrants": info.immigrants,
            "population": info.population,
            "land": info.land,
            "harvest": info.harvest,
            "rats": info.rats,
            "land_price": info.land_price,
            "grain_stock": info.grain_stock
        }
        try:
            with open(self.__filename, 'w') as f:
                json.dump(game_data, f, indent=4)
        except IOError as e:
            print(f"Error saving game state: {e}")

    def load_game_state(self) -> tuple:
        """Load the game state from a JSON file."""
        try:
            with open(self.__filename, 'r') as f:
                game_data = json.load(f)

            info = Info(
                starved=game_data["starved"],
                immigrants=game_data["immigrants"],
                population=game_data["population"],
                land=game_data["land"],
                harvest=game_data["harvest"],
                rats=game_data["rats"],
                land_price=game_data["land_price"],
                grain_stock=game_data["grain_stock"]
            )
            year = game_data["year"]
            return info, year
        except (IOError, json.JSONDecodeError, KeyError) as e:
            print(f"Error loading game state: {e}")
            return None, None

    def delete_game_state(self) -> None:
        """Delete the saved game state file."""
        try:
            import os
            if os.path.exists(self.__filename):
                os.remove(self.__filename)
        except IOError as e:
            print(f"Error deleting game state: {e}")

    def game_state_exists(self) -> bool:
        """Check if a saved game state exists."""
        try:
            import os
            return os.path.exists(self.__filename)
        except Exception as e:
            print(f"Error checking game state: {e}")
            return False

