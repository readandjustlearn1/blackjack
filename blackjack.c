#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int player1_bet, player2_bet, player1_total, player2_total, croupier_total;
char player1_name[100], player2_name[100];

void get_player_info() {
    printf("Enter first player's name: ");
    scanf("%s", player1_name);
    printf("Enter bet for %s: ", player1_name);
    scanf("%d", &player1_bet);
    printf("Enter second player's name: ");
    scanf("%s", player2_name);
    printf("Enter bet for %s: ", player2_name);
    scanf("%d", &player2_bet);
    printf("%s bet %d\n%s bet %d\n", player1_name, player1_bet, player2_name, player2_bet);
}

void deal_cards() {
    srand(time(0));
    int card1 = rand() % 12 + 1;
    int card2 = rand() % 12 + 1;
    player1_total = card1 + card2;
    printf("%s's cards: %d, %d\nTotal: %d\n", player1_name, card1, card2, player1_total);
    card1 = rand() % 12 + 1;
    card2 = rand() % 12 + 1;
    player2_total = card1 + card2;
    printf("%s's cards: %d, %d\nTotal: %d\n", player2_name, card1, card2, player2_total);
}

void player_turn(char* name, int* total, int bet) {
    int choice;
    while (*total < 21) {
        printf("%s, would you like to take another card? (1 for yes, 0 for no): ", name);
        scanf("%d", &choice);
        if (choice == 1) {
            int card = rand() % 12 + 1;
            *total += card;
            printf("%s's new card: %d\nTotal: %d\n", name, card, *total);
        }
        else break;
    }
    if (*total > 21) {
        printf("%s lost %d\n", name, bet);
        *total = 0;
    }
}

void croupier_turn() {
    croupier_total = rand() % 12 + 1 + rand() % 12 + 1;
    printf("Croupier's cards: %d, %d\nTotal: %d\n", croupier_total - (rand() % 12 + 1), (rand() % 12 + 1), croupier_total);
    while (croupier_total < 17) {
        int card = rand() % 12 + 1;
        croupier_total += card;
        printf("Croupier's new card: %d\nTotal: %d\n", card, croupier_total);
    }
}

void check_winner() {
    int winner = 0;
    int winner_total = 0;
    if (player1_total > winner_total && player1_total <= 21) {
        winner = 1;
        winner_total = player1_total;
    }
    if (player2_total > winner_total && player2_total <= 21) {
        winner = 2;
        winner_total = player2_total;
    }
    if (croupier_total > winner_total && croupier_total <= 21) {
        winner = 3;
        winner_total = croupier_total;
    }
    if (winner == 1) {
        printf("%s wins with %d\n", player1_name, player1_total);
        printf("%s gains %d\n", player1_name, player1_bet);
    }
    else if (winner == 2) {
        printf("%s wins with %d\n", player2_name, player2_total);
        printf("%s gains %d\n", player2_name, player2_bet);
    }
    else if (winner == 3) {
        printf("Croupier wins with %d\n", croupier_total);
        printf("%s loses %d\n%s loses %d\n", player1_name, player1_bet, player2_name, player2_bet);
    }
    else {
        printf("It's a tie\n%s gets %d back\n%s gets %d back\n", player1_name, player1_bet, player2_name, player2_bet);
    }
}

int main() {
    get_player_info();
    deal_cards();
    player_turn(player1_name, &player1_total, player1_bet);
    player_turn(player2_name, &player2_total, player2_bet);
    croupier_turn();
    check_winner();
    return 0;
}

