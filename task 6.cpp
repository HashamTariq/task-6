#include <iostream>
#include <string>
#include <vector>

using namespace std;

const double SAND_GRAVEL_MIN_WEIGHT = 49.9;
const double SAND_GRAVEL_MAX_WEIGHT = 50.1;
const double CEMENT_MIN_WEIGHT = 24.9;
const double CEMENT_MAX_WEIGHT = 25.1;
const double PRICE_CEMENT = 3.0;
const double PRICE_GRAVEL = 2.0;
const double PRICE_SAND = 2.0;
const double PRICE_SPECIAL_PACK = 10.0;

struct Sack {
    char contents;
    double weight;
};

bool isValidWeight(double weight, char content) {
    if (content == 'C') {
        return weight > CEMENT_MIN_WEIGHT && weight < CEMENT_MAX_WEIGHT;
    } else if (content == 'G' || content == 'S') {
        return weight > SAND_GRAVEL_MIN_WEIGHT && weight < SAND_GRAVEL_MAX_WEIGHT;
    }
    return false;
}

double calculateRegularPrice(int cementCount, int gravelCount, int sandCount) {
    return cementCount * PRICE_CEMENT + gravelCount * PRICE_GRAVEL + sandCount * PRICE_SAND;
}

double calculateDiscountedPrice(int& cementCount, int& gravelCount, int& sandCount, int& specialPacks) {
    double discountedPrice = calculateRegularPrice(cementCount, gravelCount, sandCount);

    while (cementCount >= 1 && sandCount >= 2 && gravelCount >= 2) {
        specialPacks++;
        cementCount -= 1;
        sandCount -= 2;
        gravelCount -= 2;
        discountedPrice -= PRICE_CEMENT + 2 * PRICE_SAND + 2 * PRICE_GRAVEL - PRICE_SPECIAL_PACK;
    }

    return discountedPrice;
}

void getSackWeight(char type, vector<Sack>& order) {
    double weight;
    bool validWeight;
    do {
        cout << "Enter weight for " << type << " sack: ";
        cin >> weight;
        validWeight = isValidWeight(weight, type);
        if (!validWeight) {
            cout << "Invalid weight. Please try again." << endl;
        }
    } while (!validWeight);
    order.push_back({type, weight});
}

int main() {
    vector<Sack> order;
    int numCement, numGravel, numSand;
    cout << "Enter number of sacks of Cement: ";
    cin >> numCement;
    cout << "Enter number of sacks of Gravel: ";
    cin >> numGravel;
    cout << "Enter number of sacks of Sand: ";
    cin >> numSand;

    for (int i = 0; i < numCement; i++) {
        getSackWeight('C', order);
    }
    for (int i = 0; i < numGravel; i++) {
        getSackWeight('G', order);
    }
    for (int i = 0; i < numSand; i++) {
        getSackWeight('S', order);
    }

    // Calculate the regular price
    double regularPrice = calculateRegularPrice(numCement, numGravel, numSand);
    cout << "Regular price of the order: $" << regularPrice << endl;

    // Calculate discounted price
    int specialPacks = 0;
    double discountedPrice = calculateDiscountedPrice(numCement, numGravel, numSand, specialPacks);

    if (specialPacks > 0) {
        cout << "Special packs in the order: " << specialPacks << endl;
        cout << "Discounted price: $" << discountedPrice << endl;
        cout << "Amount saved: $" << regularPrice - discountedPrice << endl;
    }

    return 0;
}

