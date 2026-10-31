/* UL2IN006 — TME2, questions 2.5 et 2.6.
   Programme de demonstration et de mesures, adapte a des matrices carrees int**.
   Compilation : gcc -std=c11 -O2 -Wall -Wextra -Werror TME2_Q25_Q26.c -o tme2_matrices
   Execution   : ./tme2_matrices
*/


// genere par IA 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **alloue_matrice(int n)
{
    if (n <= 0) return NULL;
    int **m = calloc((size_t)n, sizeof *m);
    if (!m) return NULL;
    for (int i = 0; i < n; i++) {
        m[i] = malloc((size_t)n * sizeof *m[i]);
        if (!m[i]) {
            for (int j = 0; j < i; j++) free(m[j]);
            free(m);
            return NULL;
        }
    }
    return m;
}

void desalloue_matrice(int **m, int n)
{
    if (!m) return;
    for (int i = 0; i < n; i++) free(m[i]);
    free(m);
}

/* Q2.5.1 : C = A * B, pour deux matrices carrees quelconques. O(n^3). */
void multiplication_classique(int **a, int **b, int **c, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int somme = 0;
            for (int k = 0; k < n; k++)
                somme += a[i][k] * b[k][j];
            c[i][j] = somme;
        }
    }
}

/* Q2.5.2 : A triangulaire superieure, B triangulaire inferieure.
   Les termes k < max(i,j) sont nuls. Reste O(n^3). */
void multiplication_triangulaire(int **a, int **b, int **c, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int somme = 0;
            int debut = (i > j) ? i : j;
            for (int k = debut; k < n; k++)
                somme += a[i][k] * b[k][j];
            c[i][j] = somme;
        }
    }
}

/* Q2.6.1 : comparer toutes les paires de cases distinctes : O(n^4).
   1 si toutes les valeurs sont distinctes, 0 sinon. */
int toutes_differentes_lent(int **m, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = i; k < n; k++)
                for (int l = (k == i ? j + 1 : 0); l < n; l++)
                    if (m[i][j] == m[k][l]) return 0;
    return 1;
}

/* Q2.6.2 : marqueurs des valeurs 0..V-1 : O(V + n^2).
   1 = toutes distinctes ; 0 = doublon ; -1 = erreur. */
int toutes_differentes_rapide(int **m, int n, int V)
{
    if (V <= 0 || n < 0) return -1;
    unsigned char *vu = calloc((size_t)V, sizeof *vu);
    if (!vu) return -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x = m[i][j];
            if (x < 0 || x >= V) {
                free(vu);
                return -1;
            }
            if (vu[x]) {
                free(vu);
                return 0;
            }
            vu[x] = 1;
        }
    }
    free(vu);
    return 1;
}

/* Fabrique la meme instance triangulaire pour les deux algorithmes. */
void remplir_triangulaires(int **a, int **b, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            a[i][j] = (i <= j) ? rand() % 7 : 0;
            b[i][j] = (i >= j) ? rand() % 7 : 0;
        }
}

/* Matrice contenant une permutation aleatoire de 0..n*n-1 (tous distincts).
   On mesure donc le pire cas de l'algorithme de verification. */
int remplir_distincte_aleatoire(int **m, int n, int *permutation)
{
    int N = n * n;
    for (int t = 0; t < N; t++) permutation[t] = t;
    for (int t = N - 1; t > 0; t--) {
        int k = rand() % (t + 1);
        int x = permutation[t];
        permutation[t] = permutation[k];
        permutation[k] = x;
    }
    for (int t = 0; t < N; t++) m[t / n][t % n] = permutation[t];
    return 1;
}

int main(void)
{
    srand(12345);

    /* Q2.5.4 : temps sur differentes tailles n (secondes CPU). */
    const int tailles_mult[] = {20, 50, 100, 150, 200};
    FILE *f = fopen("temps_q25.txt", "w");
    if (!f) { perror("temps_q25.txt"); return 1; }
    for (size_t t = 0; t < sizeof tailles_mult / sizeof tailles_mult[0]; t++) {
        int n = tailles_mult[t];
        int **a = alloue_matrice(n), **b = alloue_matrice(n);
        int **c1 = alloue_matrice(n), **c2 = alloue_matrice(n);
        if (!a || !b || !c1 || !c2) {
            fprintf(stderr, "Echec allocation Q2.5\n");
            desalloue_matrice(a,n); desalloue_matrice(b,n);
            desalloue_matrice(c1,n); desalloue_matrice(c2,n);
            fclose(f); return 1;
        }
        remplir_triangulaires(a,b,n);
        clock_t debut = clock();
        multiplication_classique(a,b,c1,n);
        double t1 = (double)(clock() - debut) / CLOCKS_PER_SEC;
        debut = clock();
        multiplication_triangulaire(a,b,c2,n);
        double t2 = (double)(clock() - debut) / CLOCKS_PER_SEC;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (c1[i][j] != c2[i][j]) {
                    fprintf(stderr,"Produits differents a [%d][%d]\n",i,j);
                    desalloue_matrice(a,n); desalloue_matrice(b,n);
                    desalloue_matrice(c1,n); desalloue_matrice(c2,n);
                    fclose(f); return 1;
                }
        fprintf(f, "%d %.9f %.9f\n", n, t1, t2);
        printf("Q2.5 n=%d : classique=%.6fs, triangulaire=%.6fs\n",n,t1,t2);
        desalloue_matrice(a,n); desalloue_matrice(b,n);
        desalloue_matrice(c1,n); desalloue_matrice(c2,n);
    }
    fclose(f);

    /* Q2.6.3 : 50 tirages differents par taille, moyenne des temps. */
    const int tailles_verif[] = {5, 10, 15, 20, 25, 30};
    const int essais = 50;
    f = fopen("temps_q26.txt", "w");
    if (!f) { perror("temps_q26.txt"); return 1; }
    for (size_t t = 0; t < sizeof tailles_verif / sizeof tailles_verif[0]; t++) {
        int n = tailles_verif[t], V = n * n;
        int **m = alloue_matrice(n);
        int *permutation = malloc((size_t)V * sizeof *permutation);
        if (!m || !permutation) {
            fprintf(stderr,"Echec allocation Q2.6\n");
            desalloue_matrice(m,n); free(permutation); fclose(f);
            return 1;
        }
        double total_lent = 0, total_rapide = 0;
        for (int essai = 0; essai < essais; essai++) {
            remplir_distincte_aleatoire(m,n,permutation);
            clock_t debut = clock();
            int r1 = toutes_differentes_lent(m,n);
            total_lent += (double)(clock() - debut) / CLOCKS_PER_SEC;
            debut = clock();
            int r2 = toutes_differentes_rapide(m,n,V);
            total_rapide += (double)(clock() - debut) / CLOCKS_PER_SEC;
            if (r1 != 1 || r2 != 1) {
                fprintf(stderr,"Erreur verification Q2.6\n");
                desalloue_matrice(m,n); free(permutation); fclose(f);
                return 1;
            }
        }
        fprintf(f,"%d %.9f %.9f\n",n,total_lent/essais,total_rapide/essais);
        printf("Q2.6 n=%d : lent=%.6fs, rapide=%.6fs (moy. %d tests)\n",
               n,total_lent/essais,total_rapide/essais,essais);
        desalloue_matrice(m,n); free(permutation);
    }
    fclose(f);
    puts("Fichiers crees : temps_q25.txt et temps_q26.txt");
    return 0;
}
