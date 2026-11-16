/*
 * FixtureGen - CP-085
 * Round-Robin Tournament Scheduling Engine
 * C99 console application
 *
 * Compile:
 *   macOS/Linux: gcc -std=c99 -Wall -Wextra main.c -o fixturegen
 *   Windows (MinGW): gcc -std=c99 -Wall -Wextra main.c -o fixturegen.exe
 */
#include <stdio.h>
#include <string.h>

#define MAX_TEAMS 20
#define MAX_MATCHES ((MAX_TEAMS * (MAX_TEAMS - 1)) / 2)
#define NAME_LEN 50

typedef struct {
    int id;
    char name[NAME_LEN];
} Team;

typedef struct {
    int team1;
    int team2;
    int played;
    int score1;
    int score2;
} Match;

typedef struct {
    int teamIndex;
    int played, wins, draws, losses;
    int goalsFor, goalsAgainst, goalDifference, points;
} Standing;

Team teams[MAX_TEAMS];
Match matches[MAX_MATCHES];
int teamCount = 0;
int matchCount = 0;
int fixturesGenerated = 0;

void clearInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int findTeamById(int id) {
    for (int i = 0; i < teamCount; i++)
        if (teams[i].id == id) return i;
    return -1;
}

void registerTeam(void) {
    if (fixturesGenerated) {
        printf("\nFixtures already generated. Team registration is closed.\n");
        return;
    }
    if (teamCount >= MAX_TEAMS) {
        printf("\nMaximum of %d teams reached.\n", MAX_TEAMS);
        return;
    }

    char name[NAME_LEN];
    printf("Enter team name: ");
    if (scanf(" %49[^\n]", name) != 1) {
        printf("Invalid name.\n");
        clearInput();
        return;
    }

    for (int i = 0; i < teamCount; i++) {
        if (strcmp(teams[i].name, name) == 0) {
            printf("That team is already registered.\n");
            return;
        }
    }

    teams[teamCount].id = teamCount + 1;
    strcpy(teams[teamCount].name, name);
    teamCount++;
    printf("Team '%s' registered successfully. Team ID: %d\n",
           name, teamCount);
}

void listTeams(void) {
    if (teamCount == 0) {
        printf("\nNo teams registered yet.\n");
        return;
    }
    printf("\n--- REGISTERED TEAMS ---\n");
    for (int i = 0; i < teamCount; i++)
        printf("%2d. %s\n", teams[i].id, teams[i].name);
}

void generateFixtures(void) {
    if (fixturesGenerated) {
        printf("\nFixtures have already been generated.\n");
        return;
    }
    if (teamCount < 2) {
        printf("\nRegister at least 2 teams first.\n");
        return;
    }

    matchCount = 0;
    /* Each unique pair appears exactly once: n*(n-1)/2 matches. */
    for (int i = 0; i < teamCount; i++) {
        for (int j = i + 1; j < teamCount; j++) {
            matches[matchCount].team1 = i;
            matches[matchCount].team2 = j;
            matches[matchCount].played = 0;
            matches[matchCount].score1 = 0;
            matches[matchCount].score2 = 0;
            matchCount++;
        }
    }
    fixturesGenerated = 1;

    printf("\nFixtures generated successfully!\n");
    printf("Number of teams: %d\n", teamCount);
    printf("Total matches: %d\n", matchCount);
    printf("Formula: n * (n - 1) / 2 = %d * %d / 2 = %d\n",
           teamCount, teamCount - 1, matchCount);
}

void showFixtures(void) {
    if (!fixturesGenerated) {
        printf("\nGenerate fixtures first.\n");
        return;
    }
    printf("\n--- TOURNAMENT FIXTURES ---\n");
    for (int i = 0; i < matchCount; i++) {
        printf("Match %2d: %-20s vs %-20s",
               i + 1,
               teams[matches[i].team1].name,
               teams[matches[i].team2].name);
        if (matches[i].played)
            printf("  Result: %d - %d",
                   matches[i].score1, matches[i].score2);
        else
            printf("  [Not played]");
        printf("\n");
    }
}

void recordResult(void) {
    if (!fixturesGenerated) {
        printf("\nGenerate fixtures first.\n");
        return;
    }

    showFixtures();
    int number;
    printf("\nEnter match number to record/update (1-%d): ", matchCount);
    if (scanf("%d", &number) != 1) {
        printf("Invalid input.\n");
        clearInput();
        return;
    }
    if (number < 1 || number > matchCount) {
        printf("Invalid match number.\n");
        return;
    }

    Match *m = &matches[number - 1];
    int a, b;
    printf("Enter goals for %s: ", teams[m->team1].name);
    if (scanf("%d", &a) != 1 || a < 0) {
        printf("Score must be a non-negative integer.\n");
        clearInput();
        return;
    }
    printf("Enter goals for %s: ", teams[m->team2].name);
    if (scanf("%d", &b) != 1 || b < 0) {
        printf("Score must be a non-negative integer.\n");
        clearInput();
        return;
    }

    m->score1 = a;
    m->score2 = b;
    m->played = 1;
    printf("Result saved: %s %d - %d %s\n",
           teams[m->team1].name, a, b, teams[m->team2].name);
}

void calculateStandings(Standing table[]) {
    for (int i = 0; i < teamCount; i++) {
        table[i].teamIndex = i;
        table[i].played = table[i].wins = table[i].draws = table[i].losses = 0;
        table[i].goalsFor = table[i].goalsAgainst = 0;
        table[i].goalDifference = table[i].points = 0;
    }

    for (int i = 0; i < matchCount; i++) {
        Match m = matches[i];
        if (!m.played) continue;

        Standing *a = &table[m.team1];
        Standing *b = &table[m.team2];

        a->played++;
        b->played++;
        a->goalsFor += m.score1;
        a->goalsAgainst += m.score2;
        b->goalsFor += m.score2;
        b->goalsAgainst += m.score1;

        if (m.score1 > m.score2) {
            a->wins++;
            b->losses++;
            a->points += 3;
        } else if (m.score1 < m.score2) {
            b->wins++;
            a->losses++;
            b->points += 3;
        } else {
            a->draws++;
            b->draws++;
            a->points++;
            b->points++;
        }
    }

    for (int i = 0; i < teamCount; i++)
        table[i].goalDifference = table[i].goalsFor - table[i].goalsAgainst;
}

int comesBefore(Standing a, Standing b) {
    if (a.points != b.points) return a.points > b.points;
    if (a.goalDifference != b.goalDifference)
        return a.goalDifference > b.goalDifference;
    return a.goalsFor > b.goalsFor;
}

void showPointsTable(void) {
    if (!fixturesGenerated) {
        printf("\nGenerate fixtures first.\n");
        return;
    }

    Standing table[MAX_TEAMS];
    calculateStandings(table);

    /* Selection sort: points first, then goal difference, then goals scored. */
    for (int i = 0; i < teamCount - 1; i++) {
        int best = i;
        for (int j = i + 1; j < teamCount; j++)
            if (comesBefore(table[j], table[best])) best = j;
        if (best != i) {
            Standing temp = table[i];
            table[i] = table[best];
            table[best] = temp;
        }
    }

    printf("\n================ POINTS TABLE ================\n");
    printf("%-4s %-20s %3s %3s %3s %3s %4s %4s %4s %4s\n",
           "Pos", "Team", "P", "W", "D", "L", "GF", "GA", "GD", "Pts");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < teamCount; i++) {
        Standing s = table[i];
        printf("%-4d %-20s %3d %3d %3d %3d %4d %4d %4d %4d\n",
               i + 1, teams[s.teamIndex].name,
               s.played, s.wins, s.draws, s.losses,
               s.goalsFor, s.goalsAgainst, s.goalDifference, s.points);
    }
    printf("\nP=Played W=Wins D=Draws L=Losses GF=Goals For ");
    printf("GA=Goals Against GD=Goal Difference Pts=Points\n");
    printf("Points: Win = 3, Draw = 1, Loss = 0.\n");
    printf("Ranking: Points, then Goal Difference, then Goals For.\n");
}

void showMenu(void) {
    printf("\n========== FIXTUREGEN: TOURNAMENT MANAGER ==========\n");
    printf("1. Register team\n");
    printf("2. View registered teams\n");
    printf("3. Generate round-robin fixtures\n");
    printf("4. View fixtures\n");
    printf("5. Record match result\n");
    printf("6. Display points table\n");
    printf("7. Exit\n");
    printf("Choose an option: ");
}

int main(void) {
    int choice;
    printf("Welcome to FixtureGen - Round-Robin Tournament Scheduling Engine\n");

    do {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Please enter a number from 1 to 7.\n");
            clearInput();
            continue;
        }

        switch (choice) {
            case 1: registerTeam(); break;
            case 2: listTeams(); break;
            case 3: generateFixtures(); break;
            case 4: showFixtures(); break;
            case 5: recordResult(); break;
            case 6: showPointsTable(); break;
            case 7: printf("\nThank you for using FixtureGen!\n"); break;
            default: printf("Invalid choice. Select 1 to 7.\n");
        }
    } while (choice != 7);

    return 0;
}