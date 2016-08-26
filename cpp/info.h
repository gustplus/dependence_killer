#ifndef DEPENDENCES_KILLER_INFO_H_
#define DEPENDENCES_KILLER_INFO_H_

#define SQRT_TWO 1.414213

class Info {
public:
	Info() : R(0), N(0), AC(0), Ce(0), Ca(0), H(0.0), A(0.0), I(0.0), D(0.0) {}

	int R;		//包内部类的关系数目
	int N;		//包内类总数
	int AC;		//抽象类数目
	int Ce;		//输入耦合度(对本包有依赖的包的数目)
	int Ca;		//输出耦合度(被本包依赖的包的数目)

	float GetH() { return H; }
	float GetA() { return A; }
	float GetI() { return I; }
	float GetD2() { return D2; }
	float GetD() { return D; }
	
	void Calculate() {
		CalH(); 
		CalA(); 
		CalI(); 
		CalD2(); 
		CalD(); 
	}	
private:
	void CalH() {
		if(N == 0) return;
		H = (float)(R + 1)/N;
	}

	void CalA() {
		if(N == 0) return;
		A = (float)AC/N;
	}

	void CalI() {
		if(Ce + Ca == 0) return;
		I = (float)Ce / (Ce + Ca);
	}
	
	void CalD2() {	
		if(A == 0 && I == 0) {
			D2 = 0;
			return;
		}
		float ab = A + I - 1;
		if(ab < 0) {
			ab = -ab;
		}
		D2 = ab;
	}

	void CalD() {
		D = D2 / SQRT_TWO;
	}

	float H;	//内聚性
	float A;	//抽象性
	float I;	//不稳定性
	float D;
	float D2;
};

#endif
