# Author: Jesus Carlos Martinez Gonzalez
# Date: 20/10/2021
# Objective: Implements a dictionary's functionality
# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    # Populates the teams list with the names of the teams in the csv
    teams = []
    with open(sys.argv[1]) as csv_file:
        csv_reader = csv.DictReader(csv_file)
        for team in csv_reader:
            team['rating'] = int(team['rating'])
            teams.append(team)

    # To keep track of how many tournaments each team has won
    counts = {}
    
    # Simualtes 1000 tournaments and stores results in counts
    for i in range(1000):
        winner = simulate_tournament(teams)
        if winner in counts:
            counts[winner] += 1
        else:
            counts[winner] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


# Simulates the outcome of a match, given both team's ratings
def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


# Simulates a round within a tournament, given teams
def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


# Simulates a tournament, given teams
def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    if len(teams) == 1:
        return teams[0]['team']
    else:
        round_winners = simulate_round(teams)
        return simulate_tournament(round_winners)


if __name__ == "__main__":
    main()
