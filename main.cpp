#include <cmath>
#include <format>
#include <iostream>
#include <limits>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cout << "Break-Even Calculator\n"
	             "Model: p = y * (R * f - C) * (1 - t) - e\n"
	             "Break-even when p = 0 => y = e / ((R * f - C) * (1 - t))\n"
	             "Assume R, C, and t stay constant each year.\n"
	             "Quick f guide: 1.0 global, 0.3 regional, 0.05 normal tower.\n\n";

	auto prompt = [](const char* msg) {
		double val;
		while (true) {
			std::cout << msg;
			if (std::cin >> val && val >= 0.0) return val;
			std::cout << "Invalid input. Use a non-negative number.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	};

	const double e = prompt("Enter construction cost e (USD): ");
	const double f = prompt("Enter global fame factor f (0+): ");
	const double r = prompt("Enter annual revenue projection R (USD, before fame scaling): ");
	const double c = prompt("Enter annual operating cost C (USD): ");
	const double t = prompt("Enter effective tax rate t (0.0 - 0.99): ");

	// base calc
	const double rf  = r * f;
	const double n   = rf - c;
	const double nat = n * (1.0 - t);  // net annual profit after tax

	std::cout << std::format(
		"\nBreak-Even\n"
		"e: ${:.2f}\n"
		"f: {:.2f}\n"
		"R: ${:.2f}\n"
		"C: ${:.2f}\n"
		"t: {:.1f}%\n"
		"R*f: ${:.2f}\n"
		"R*f-C: ${:.2f}\n"
		"(R*f-C)*(1-t): ${:.2f}\n",
		e, f, r, c, t * 100.0, rf, n, nat);

	double y = 0.0;  // reused in sensitivity
	if (e == 0.0) {
		std::cout << "Instant profit (y = 0).\n";
	} else if (nat <= 0.0) {
		std::cout << "No break-even here (after-tax net profit <= 0).\n";
	} else {
		y = e / nat;
		const double ym = y * 12.0;
		const double fy = std::ceil(y);
		std::cout << std::format(
			"Break-even y: {:.2f} years ({:.1f} months)\n"
			"First full profitable year: {:.0f}\n",
			y, ym, fy);
	}

	std::cout << "\n--- Sensitivity ---\n"
	             "Case 1: f drops 20% (fame shock).\n"
	             "Case 2: C rises 15% (cost overrun).\n"
	             "Keeping other variables fixed.\n";

	constexpr double FAME_DROP = 0.8;
	constexpr double COST_RISE = 1.15;
	const bool zero_e = (e == 0.0);
	const bool no_profit = (nat <= 0.0);

	const double dn1 = (r * f * FAME_DROP - c) * (1.0 - t);
	const double dn2 = (rf - c * COST_RISE) * (1.0 - t);

	auto sensitivity_case = [&](const char* name, double net_scenario) {
		std::cout << "-- " << name << " --\n";
		if (zero_e) {
			std::cout << "Both cases: 0 years\n";
		} else if (no_profit) {
			std::cout << "Base case already never breaks even.\n";
		} else if (net_scenario <= 0.0) {
			std::cout << "Base case breaks even, " << name << " case does not.\n";
		} else {
			const double y_scenario = e / net_scenario;
			std::cout << std::format(
				"Base y: {:.2f} years\n"
				"{}: {:.2f} years\n"
				"Extra years: {:.2f}\n",
				y, name, y_scenario, y_scenario - y);
		}
	};

	sensitivity_case("Fame drop (20%)", dn1);
	sensitivity_case("Cost overrun (15%)", dn2);

	std::cout << "\nNote: While real competition is gradual, this is just a stress test.\n";

	return 0;
}