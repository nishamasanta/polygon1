#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>

using namespace std;

// Helper function to compute the squared distance between two points
int squaredDistance(pair<int, int> a, pair<int, int> b) {
    return (a.first - b.first) * (a.first - b.first) +
           (a.second - b.second) * (a.second - b.second);
}

// Normalize the polygon based on relative distances
vector<int> normalizePolygon(const vector<pair<int, int>>& vertices) {
    int n = vertices.size();
    vector<int> distances;

    // Compute squared distances between consecutive vertices
    for (int i = 0; i < n; i++) {
        distances.push_back(squaredDistance(vertices[i], vertices[(i + 1) % n]));
    }

    // Generate all cyclic rotations and find the lexicographically smallest one
    vector<int> bestRotation = distances;
    for (int i = 1; i < n; i++) {
        vector<int> rotated;
        for (int j = 0; j < n; j++) {
            rotated.push_back(distances[(i + j) % n]);
        }
        bestRotation = min(bestRotation, rotated);
    }

    return bestRotation;
}

// Function to find matching earrings
void findMatchingEarrings(int N, const vector<vector<pair<int, int>>>& polygons) {
    vector<vector<int>> normalizedPolygons;

    // Normalize all polygons
    for (const auto& vertices : polygons) {
        normalizedPolygons.push_back(normalizePolygon(vertices));
    }

    // Compare all pairs of normalized polygons
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (normalizedPolygons[i] == normalizedPolygons[j]) {
                // Print the result as required: a single line with indices
                cout << i + 1 << " " << j + 1;
                return;
            }
        }
    }
}

int main() {
    int N; // Number of earring pieces
    cin >> N;

    vector<vector<pair<int, int>>> polygons(N);

    for (int i = 0; i < N; i++) {
        int K; // Number of vertices for the current polygon
        cin >> K;

        polygons[i].resize(K);
        for (int j = 0; j < K; j++) {
            cin >> polygons[i][j].first >> polygons[i][j].second;
        }
    }

    findMatchingEarrings(N, polygons);

    return 0;
}
