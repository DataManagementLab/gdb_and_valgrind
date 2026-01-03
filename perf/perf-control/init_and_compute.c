#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


typedef struct {
    double x, y;
} Node;

typedef struct {
    int n1, n2, n3, n4;   // quad element
} Element;

typedef struct {
    Node *nodes;
    Element *elements;
    int num_nodes;
    int num_elements;
} Mesh;

/* ---------------- Mesh generation (INIT) with Randomness ---------------- */

Mesh generate_mesh(int nx, int ny) {
    Mesh mesh;
    mesh.num_nodes = (nx + 1) * (ny + 1);
    mesh.num_elements = nx * ny;

    mesh.nodes = malloc(mesh.num_nodes * sizeof(Node));
    mesh.elements = malloc(mesh.num_elements * sizeof(Element));

    if (!mesh.nodes || !mesh.elements) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Seed the random number generator
    srand(time(NULL));

    /* Tolerance defines how much a node can move. 
       We keep it under 0.5/nx to ensure nodes don't cross each other 
       and invert the elements.
    */
    double jitter_strength = 0.4; 
    double dx = 1.0 / nx;
    double dy = 1.0 / ny;

    int idx = 0;
    for (int j = 0; j <= ny; j++) {
        for (int i = 0; i <= nx; i++) {
            double rx = 0.0;
            double ry = 0.0;

            /* Only jitter internal nodes; keep boundaries perfect */
            if (i > 0 && i < nx && j > 0 && j < ny) {
                // Generates a value between -0.5 and 0.5
                rx = ((double)rand() / RAND_MAX - 0.5) * dx * jitter_strength;
                ry = ((double)rand() / RAND_MAX - 0.5) * dy * jitter_strength;
            }

            mesh.nodes[idx].x = ((double)i / nx) + rx;
            mesh.nodes[idx].y = ((double)j / ny) + ry;
            idx++;
        }
    }

    /* Generate quad connectivity (Remains the same) */
    idx = 0;
    for (int j = 0; j < ny; j++) {
        for (int i = 0; i < nx; i++) {
            int n0 = j * (nx + 1) + i;
            mesh.elements[idx++] = (Element){
                n0,
                n0 + 1,
                n0 + (nx + 1) + 1,
                n0 + (nx + 1)
            };
        }
    }

    return mesh;
}

/* ---------------- Heavy computation ---------------- */

double heavy_compute(const Mesh *mesh, int iterations) {
    double result = 0.0;

    for (int it = 0; it < iterations; it++) {
        for (int e = 0; e < mesh->num_elements; e++) {
            Element el = mesh->elements[e];

            Node a = mesh->nodes[el.n1];
            Node b = mesh->nodes[el.n2];
            Node c = mesh->nodes[el.n3];
            Node d = mesh->nodes[el.n4];

            /* Fake FEM-style math */
            double cx = 0.25 * (a.x + b.x + c.x + d.x);
            double cy = 0.25 * (a.y + b.y + c.y + d.y);

            result += sin(cx * cy) * cos(cx + cy);
        }
    }

    return result;
}

/* ---------------- Main ---------------- */

#define FIFO_PATH "/tmp/perf_fifo"

int main(int argc, char** argv) {
    if (argc > 2) {
        printf("Usage: ./init_then_compute ${0|1}");
        return -1;
    }
    int profile_init = 0;
    if (argc == 2) {
        profile_init = atoi(argv[1]);
    }
    const int nx = 1000;
    const int ny = 10000;
    const int iterations = 100;
    mkfifo(FIFO_PATH, 0666);

    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd < 0) {
        printf("Failed to open control fifo\n");
        return -1;
    }

    clock_t t0 = clock();
    if (profile_init) {
        write(fd, "enable\n", 8);
    }
    Mesh mesh = generate_mesh(nx, ny);
    if (profile_init) {
        write(fd, "disable\n", 9);
    }
    clock_t t1 = clock();

    if (!profile_init) {
        write(fd, "enable\n", 8);
    }
    double value = heavy_compute(&mesh, iterations);
    if (!profile_init) {
        write(fd, "disable\n", 9);
    }
    clock_t t2 = clock();

    printf("Mesh: %d nodes, %d elements\n",
           mesh.num_nodes, mesh.num_elements);

    printf("Init time:    %.3f s\n",
           (double)(t1 - t0) / CLOCKS_PER_SEC);
    printf("Compute time: %.3f s\n",
           (double)(t2 - t1) / CLOCKS_PER_SEC);

    printf("Result: %f\n", value);

    free(mesh.nodes);
    free(mesh.elements);
    return 0;
}
