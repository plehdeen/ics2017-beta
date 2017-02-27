#include "trap.h"
#include "FLOAT.h"

#define check(real, test) nemu_assert(Fabs(f2F(real) - test) < f2F(1e-4))

/* solve 0.5x^2 + 0.5x - 0.5 = 0 */

int main() {
	FLOAT a = f2F(0.5);
	FLOAT b = f2F(0.5);
	FLOAT c = f2F(-0.5);

	FLOAT bb = F_mul_F(b, b);
	check(0.25, bb);

	FLOAT dt = bb - F_mul_F(F_mul_int(a, 4), c);
	check(1.25, dt);

	FLOAT sqrt_dt = sqrt(dt);
	check(1.118034, sqrt_dt);

	FLOAT x1 = F_div_F(-b + sqrt_dt, F_mul_int(a, 2));
	check(0.618, x1);

	FLOAT x2 = F_div_F(-b - sqrt_dt, F_mul_int(a, 2));
	check(-1.618, x2);

	return 0;
}
