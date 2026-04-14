#include <stdio.h>
#include <math.h>

const int PRIX_STANDARD = 20; // en centimes

typedef struct call_record {
  size_t no_client; // numéro client
  int no_tel_appel; // numéro de tel appelé
  int date;         // la date
  int minutes;      // la durée de l'appel
} call_record_t;

typedef struct cost {
  int tel;                 // numéro de tel
  int centimes_par_minute; // tarif
} cost_t;

void load_n_call_records(call_record_t records[], size_t n) {
  for (size_t i = 0; i < n; i++) {
    // On peut directement donner les adresses des champs du record à scanf
    // On utilise un pointeur vers le record pour raccourcir
    call_record_t *r = &records[i];
    scanf("%lu %d %d %d", &r->no_client, &r->date, &r->no_tel_appel, &r->minutes);
  }
}

void load_n_costs(cost_t costs[], size_t n) {
  for (size_t i = 0; i < n; i++) {
    // Ici une autre possibilité : on lit dans des variables locales
    int tel;
    double chf_par_minutes;
    scanf("%d %lf", &tel, &chf_par_minutes);

    // Puis on assigne aux champs
    // On doit faire ça ici pour la conversion de CHF en centimes.
    // Challenge : pourrait-on lire les CHF sans utiliser de double ?
    costs[i].tel = tel;
    costs[i].centimes_par_minute = (int) round(chf_par_minutes * 100.0);
  }
}

void temps_total(
    const call_record_t records[], size_t M, int total_minutes[], size_t C) {
  for (size_t i = 0; i < C; i++) {
    total_minutes[i] = 0;
  }

  for (size_t i = 0; i < M; i++) {
    total_minutes[records[i].no_client] += records[i].minutes;
  }
}

void temps_total_mois(
    const call_record_t records[], size_t M, int mois,
    int total_minutes[], size_t C) {
  for (size_t i = 0; i < C; i++)
    total_minutes[i] = 0;

  for (size_t i = 0; i < M; i++) {
    if (records[i].date / 100 == mois) {
      total_minutes[records[i].no_client] += records[i].minutes;
    }
  }
}

int centimes_minute(const cost_t costs[], size_t C, int tel) {
  for (size_t i = 0; i < C; i++) {
    if (costs[i].tel == tel) {
      return costs[i].centimes_par_minute;
    }
  }

  return PRIX_STANDARD;
}

void centimes_total_mois(
    const call_record_t records[], const cost_t costs[], size_t M, size_t N,
    int mois, int total_cout[], size_t C) {
  for (size_t i = 0; i < C; i++)
    total_cout[i] = 0;

  for (size_t i = 0; i < M; i++) {
    if (records[i].date / 100 == mois) {
      total_cout[records[i].no_client] +=
        records[i].minutes * centimes_minute(costs, N, records[i].no_tel_appel);
    }
  }
}

void afficher_minutes(int minutes[], size_t n) {
  for (size_t i = 0; i < n; i++) {
    printf("Client %lu: %d minutes\n", i, minutes[i]);
  }
}

void afficher_cost_comme_chf(int cost) {
  int unites = cost / 100;
  int decimes = (cost / 10) % 10;
  int centimes = cost % 10;
  printf("%d.%d%d", unites, decimes, centimes);
}

void afficher_chf(const int cout[], size_t n) {
  for (size_t i = 0; i < n; i++) {
    printf("Client %lu: CHF ", i);
    afficher_cost_comme_chf(cout[i]);
    printf("\n");
  }
}

int main() {
  size_t C, M, N;
  scanf("%lu %lu %lu", &C, &M, &N);

  call_record_t records[M];
  cost_t costs[N];

  load_n_call_records(records, M);
  load_n_costs(costs, N);

  int total_minutes[C];
  temps_total(records, M, total_minutes, C);
  afficher_minutes(total_minutes, C);

  temps_total_mois(records, M, 202401, total_minutes, C);
  printf("***\n");
  printf("Minutes janvier 2024\n");
  afficher_minutes(total_minutes, C);

  temps_total_mois(records, M, 202311, total_minutes, C);
  printf("***\n");
  printf("Minutes novembre 2023\n");
  afficher_minutes(total_minutes, C);

  int total_cout[C];
  centimes_total_mois(records, costs, M, N, 202311, total_cout, C);
  printf("***\n");
  printf("CHF novembre 2023\n");
  afficher_chf(total_cout, C);

  centimes_total_mois(records, costs, M, N, 202308, total_cout, C);
  printf("***\n");
  printf("CHF aout 2023\n");
  afficher_chf(total_cout, C);
}

