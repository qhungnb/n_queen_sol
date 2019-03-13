// Nguyen Quoc Hung

#include<bits/stdc++.h>
using namespace std;

#define e 2.718281828459045 //double
#define N 3000
#define Test 10000000

typedef long long ll;

vector<int> X;
vector<ll> crossL, crossR;
int num_ans = 0, n = 8, nummin=(int)1e9, nummax, num;

double getRand(){
    return (double)(rand()%1001)/1000;
}


int F(vector<int> answers){
    int fitness = 0;
    for(int queen=0; queen<n; queen++){    //for each queen
        for(int nextqueen = queen + 1; nextqueen<n; nextqueen++){        //for each of the other queens (nextqueen = queen to avoid counting pairs twice)
            if(answers[queen] == answers[nextqueen] || abs(queen-nextqueen)==abs(answers[queen]-answers[nextqueen])){   //if conflict
                fitness++;
            }
        }
    }
    return fitness;
}

void printsolution(vector<int> solution){
    if (F(solution)) cout <<  1 << endl;
    num_ans++;
    cout << "Answer " << num_ans << ": " << endl;

    for (int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if (solution[i]==j) cout << "Q";
            else cout << ".";
        }
        cout << endl;
    }
    cout << endl;
}

void prepare() {
    fill(crossL.begin(), crossL.end(), 0);
    fill(crossR.begin(), crossR.end(), 0);
    num = 0;

    for(int i=0; i<n; i++) {
        X[i] = i;
        crossL[n+i-X[i]]++;
        crossR[i+X[i]]++;
    }
}


ll fitness(vector<int> X) {
    ll ans = 0;
    for (int i=0; i<2*n; i++) ans+= crossL[i]*(crossL[i]-1) + crossR[i]*(crossR[i]-1);
    return ans;
}

ll Fitness(ll fitnessx, int pos[]) {
    ll fitness = fitnessx;
    for (int i=0; i<2; i++) {
        crossL[n+pos[i]-X[pos[i]]]--;
        crossR[pos[i]+X[pos[i]]]--;

        fitness = fitness - 2*crossL[n+pos[i]-X[pos[i]]] - 2*crossR[pos[i]+X[pos[i]]];
    }
    //if (fitness > fitnessx) cout << 1 << endl;

    swap(X[pos[0]], X[pos[1]]);

    for (int i=0; i<2; i++) {
        fitness = fitness + 2*(crossL[n+pos[i]-X[pos[i]]]) + 2*(crossR[pos[i]+X[pos[i]]]);
        crossL[n+pos[i]-X[pos[i]]]++;
        crossR[pos[i]+X[pos[i]]]++;
    }

    return fitness;
}

int SimulatedAnnealing(double alpha, double T, int n){
    prepare();
    ll fitnessx = fitness(X);

    for (int t=0; t<Test; t++){
        int pos[2];
        pos[0] = rand()%n;
        pos[1] = rand()%n; // heuristic chon 2 vi tri de hoan doi
        if (pos[0]==pos[1]) continue;
        //cout << pos1 << " " << pos2 << endl;
        ll fitnessy = Fitness(fitnessx, pos);  //tinh gia tri ham danh gia cho phuong an moi
        num++;

        double tmp =  fitnessx - fitnessy;
        if(tmp>0 || getRand() < pow(e, tmp/T)){ //Dieu kien chon phuong an
            fitnessx = fitnessy;  // Chon phuong an nay
            //cout << tmp << endl;
        }
        else fitnessx = Fitness(fitnessy, pos); // trao doi lai 2 vi tri neu khong chon phuong an nay

        if(fitnessx==0){
            printsolution(X);
            nummin = min(nummin, t);
            nummax = max(nummax, t);
            return 1;
        }
        T *= alpha;  //Giam nhiet do
    }

    return 0;
}

int main() {
    srand(time(0));
    //freopen("nqueen.in", "r", stdin);
    //freopen("nqueen.out", "w", stdout);

    for (int t=0; t<15; t++) {
        nummin = Test; nummax = 0; num_ans=0;
        cout << "Nhap n(n > 3): ";
        cin >> n;
        X = vector<int>(n);

        //cout << n << endl;

        crossL = crossR = vector<ll>(2*n);

        for (int k=0; k<10; k++) {
            //for(int i=0; i<n; i++) cin >> X[i];
            for(int i=0; i<n; i++) X[i] = rand()%n;
            SimulatedAnnealing(0.99, 1000, n);
        }
        double average = nummin+nummax; average/=2;
        //printf("%d %d %d %.2f %.4f\n", n, nummin, nummax, average, average/(n*n));
    }
    return 0;
}
