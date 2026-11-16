# FixtureGen – Round-Robin Tournament Scheduling Engine

FixtureGen is a C-based tournament management application designed to make organising round-robin competitions easier and more systematic. Through a simple menu-driven console interface, organisers can register teams, generate fixtures, enter match results, calculate team statistics and view an automatically ranked points table.

A single round-robin tournament is a format in which every participating team competes against every other team exactly once. FixtureGen automates the creation of these match pairings and helps keep the tournament results and standings organised in one place.

## Project Team

| Sl. No. | Name | USN | Branch |
|:---:|---|---|---|
| 1 | Sanjay J S | 1AT24EC137 | Electronics and Communication Engineering (ECE) |
| 2 | Shravanth S | 1AT24EC144 | Electronics and Communication Engineering (ECE) |

**Institution:** Atria Institute of Technology

---

## Overview

Managing a tournament manually can become difficult as the number of participating teams increases. Organisers need to ensure that every team receives the correct set of fixtures, match results are recorded consistently, and standings are updated accurately.

FixtureGen addresses these tasks with a structured C program. It stores team and match information, generates all unique team pairings, records scores and calculates the standings from the entered results.

The project is designed with separate functions for the main operations, making the code easier to understand, maintain and extend.

## Key Features

### 1. Team Registration

Organisers can add teams to a tournament by entering their names. Each registered team is assigned an ID, which is used internally to identify teams when creating fixtures and recording results.

The application also checks for duplicate team names and enforces the configured team capacity. Registration is closed after fixtures have been generated so that the existing fixture list remains consistent.

### 2. Automatic Round-Robin Fixture Generation

FixtureGen generates every unique pairing of registered teams. Each team is matched with every other team once, without creating a fixture against itself or repeating the same pairing in reverse order.

For a tournament containing `n` teams, the total number of matches is:

`M = n × (n - 1) / 2`

For example, a tournament with four teams produces six matches.

The fixture-generation logic uses nested loops. The inner loop begins at `i + 1`, ensuring that each unique pair is generated only once. The algorithm has a time complexity of `O(n²)`.

The current version generates the list of pairings; it does not yet assign dates, venues or specific playing rounds.

### 3. Match Result Recording

After fixtures have been generated, the organiser can select a match using its match number and enter the scores for both teams.

The entered result is stored against that match. The application supports updating a previously recorded result, allowing corrections to be made if a score was entered incorrectly.

### 4. Automatic Points Table

FixtureGen calculates team statistics from the recorded match results. The points table includes:

- **Played (P):** Number of matches completed by the team.
- **Wins (W):** Number of matches won.
- **Draws (D):** Number of matches drawn.
- **Losses (L):** Number of matches lost.
- **Goals For (GF):** Total goals scored by the team.
- **Goals Against (GA):** Total goals conceded by the team.
- **Goal Difference (GD):** Goals For minus Goals Against.
- **Points (Pts):** Total points earned from completed matches.

Unplayed matches are not included in the calculated statistics.

### 5. Automatic Team Ranking

After calculating the statistics, the application arranges teams in ranking order. The current ranking criteria are:

1. Higher total points.
2. Higher goal difference.
3. Higher number of goals scored.

FixtureGen uses Selection Sort to arrange the teams according to these criteria. The points table therefore updates based on the results entered by the organiser.

## Scoring System

The current implementation follows a football-style points system:

| Match Outcome | Points Awarded |
|---|:---:|
| Win | 3 |
| Draw | 1 |
| Loss | 0 |

Goal difference is calculated as:

`Goal Difference = Goals For - Goals Against`

When two teams have the same number of points, goal difference is used as the first tie-breaker. If goal difference is also equal, the team with more goals scored is ranked higher.

**About other sports:** Round-robin is a tournament format, not a football-only format. The fixture-generation algorithm can be reused for sports such as cricket, badminton, chess, basketball and table tennis. This version currently uses football-style scores and tie-breaking; other sports would require their own result fields, scoring rules and tie-breakers.

## Technologies and C Concepts

FixtureGen is developed in **C (C99)** and uses standard C programming concepts:

| Technology / Concept | How It Is Used |
|---|---|
| C programming language | Implements the tournament management application |
| Structures (`struct`) | Groups related team, match and standings data |
| Arrays | Stores registered teams, fixtures and standings |
| Functions | Separates registration, fixture generation, result entry and ranking operations |
| Nested loops | Generates every unique team pairing |
| Conditional statements | Determines match outcomes and awards points |
| Pointers | Accesses and updates selected match records |
| String handling | Stores and compares team names |
| Selection Sort | Orders teams according to their standings |

## Project Structure

```text
FixtureGen/
├── main.c
└── README.md
```

## Using the Application

When FixtureGen starts, it displays a menu similar to the following:

```text
========== FIXTUREGEN: TOURNAMENT MANAGER ==========

1. Register team
2. View registered teams
3. Generate round-robin fixtures
4. View fixtures
5. Record match result
6. Display points table
7. Exit

Choose an option:
```

Select the required operation by entering its menu number and follow the prompts displayed by the application.

A typical tournament workflow is:

1. Register all participating teams.
2. View the registered teams and confirm the list.
3. Generate the round-robin fixtures.
4. View the generated fixtures.
5. Enter the result after each match is completed.
6. Display the points table to review the latest standings.
7. Exit the application when tournament management is complete.

## Example Tournament

Consider a tournament with four teams:

- Red
- Green
- Blue
- Yellow

The generated fixtures will be:

| Match No. | Fixture |
|:---:|---|
| 1 | Red vs Green |
| 2 | Red vs Blue |
| 3 | Red vs Yellow |
| 4 | Green vs Blue |
| 5 | Green vs Yellow |
| 6 | Blue vs Yellow |

For illustration, suppose the following results are entered:

| Match | Score |
|---|:---:|
| Red vs Green | 2–1 |
| Red vs Blue | 1–1 |
| Red vs Yellow | 3–0 |
| Green vs Blue | 2–0 |
| Green vs Yellow | 1–1 |
| Blue vs Yellow | 2–0 |

The resulting standings would be:

| Position | Team | Played | Wins | Draws | Losses | GF | GA | GD | Points |
|:---:|---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| 1 | Red | 3 | 2 | 1 | 0 | 6 | 2 | +4 | 7 |
| 2 | Green | 3 | 1 | 1 | 1 | 4 | 3 | +1 | 4 |
| 3 | Blue | 3 | 1 | 1 | 1 | 3 | 3 | 0 | 4 |
| 4 | Yellow | 3 | 0 | 1 | 2 | 1 | 6 | -5 | 1 |

Green is ranked above Blue because both teams have four points, but Green has a higher goal difference.

## Current Scope and Limitations

- The current source code supports a maximum of 20 teams.
- Team and match information is stored in memory while the application is running.
- Tournament information is not retained after the application exits.
- The current scoring and tie-breaking logic is based on football-style goals.
- Fixtures are generated as pairings; dates, venues and playing rounds are not assigned.
- If teams are equal on points, goal difference and goals scored, the current version does not apply an additional tie-breaker.

## Future Development

FixtureGen can be extended into a more comprehensive tournament management application. Possible improvements include:

- **Dynamic team capacity:** Use dynamic memory allocation to support larger tournaments without a fixed team limit.
- **Persistent storage:** Use file handling to save tournament details, fixtures and results, and load them in later sessions.
- **Multiple sports:** Introduce configurable scoring systems and sport-specific statistics for cricket, badminton, chess and other competitions.
- **Advanced tie-breaking:** Add additional ranking criteria when teams remain equal after the existing comparisons.
- **Round and date scheduling:** Organise fixtures into rounds and assign match dates, times and venues.
- **Rest-day management:** Avoid scheduling a team to play on consecutive days.
- **Tournament reports:** Export fixtures, match results and final standings.
- **Graphical interface:** Develop a graphical user interface to make tournament creation and management easier.

## Conclusion

FixtureGen provides a simple and structured way to manage the core activities of a round-robin tournament. It combines team registration, automatic fixture generation, match result recording and points-table calculation in one C-based console application.

The project demonstrates how structures, arrays, functions, pointers, loops and sorting algorithms can be applied to a practical management problem. Its modular design also provides a foundation for future improvements such as persistent data storage, advanced scheduling and support for different sports.
