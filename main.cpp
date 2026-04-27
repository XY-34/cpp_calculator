#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

int main() {
	std::cout << "Break-Even Calculator\n";
	std::cout << "Model: p = y * (R * f - C) - e\n";
	std::cout << "Break-even when p = 0 => y = e / (R * f - C)\n";
	std::cout << "Assume R and C stay constant each year.\n";
	std::cout << "Quick f guide: 1.0 global, 0.3 regional, 0.05 normal tower.\n\n";

	double e;
	while (true) {
		std::cout << "Enter construction cost e (USD): ";
		if (std::cin >> e && e >= 0.0) break;
		std::cout << "Invalid input. Use a non-negative number.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	double f;
	while (true) {
		std::cout << "Enter global fame factor f (0+): ";
		if (std::cin >> f && f >= 0.0) break;
		std::cout << "Invalid input. Use a non-negative number.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	double r;
	while (true) {
		std::cout << "Enter annual revenue projection R (USD, before fame scaling): ";
		if (std::cin >> r && r >= 0.0) break;
		std::cout << "Invalid input. Use a non-negative number.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	double c;
	while (true) {
		std::cout << "Enter annual operating cost C (USD): ";
		if (std::cin >> c && c >= 0.0) break;
		std::cout << "Invalid input. Use a non-negative number.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	// base calc
	const double rf = r * f;
	const double n = rf - c;

	std::cout << std::fixed << std::setprecision(2);
	std::cout << "\nBreak-Even\n";
	std::cout << "e: $" << e << "\n";
	std::cout << "f: " << f << "\n";
	std::cout << "R: $" << r << "\n";
	std::cout << "C: $" << c << "\n";
	std::cout << "R*f: $" << rf << "\n";
	std::cout << "R*f-C: $" << n << "\n";

	if (e == 0.0) {
		std::cout << "Instant profit (y = 0).\n";
	} else if (n <= 0.0) {
		std::cout << "No break-even here (R*f - C <= 0).\n";
	} else {
		const double y = e / n;
		const double fy = std::ceil(y);
		std::cout << "Break-even y: " << y << " years\n";
		std::cout << "First full profitable year: " << fy << "\n";
	}

	std::cout << "\n--- Sensitivity ---\n";
	std::cout << "Case: f drops 20%.\n";
	std::cout << "Keeping C fixed.\n";

	// base vs drop
	const double bn = r * f - c;
	const double fd = f * 0.8;
	const double dn = r * fd - c;

	if (e == 0.0) {
		std::cout << "Baseline break-even: 0 years\n";
		std::cout << "Af.ter 20% fame drop: 0 years\n";
		std::cout << "Additional years needed: 0\n";
	} else if (bn <= 0.0) {
		std::cout << "Base case already never breaks even.\n";
	} else if (dn <= 0.0) {
		std::cout << "Base case breaks even, dropped case does not.\n";
	} else {
		const double yb = e / bn;
		const double yd = e / dn;
		const double ye = yd - yb;
		std::cout << "Base y: " << yb << " years\n";
		std::cout << "Drop y: " << yd << " years\n";
		std::cout << "Extra years: " << ye << "\n";
	}

	std::cout << "\nNote: While real competition is gradual, this is just a stress test.\n";

	return 0;
}