If megatall skyscrapes are so profitable and recognizable, why doesn't every city build one? This model will answer why.

Model structure:

Net profit after y years:

p = y(Rf - C) - e

Variables:
- e: construction cost (USD)
- R: annual revenue projection (USD)
- f: fame multiplier
- C: annual operating cost (USD)
- y: years since opening

Break-even condition p = 0:

y = e / (Rf - C)

If Rf - C <= 0, the project will never break even in this model.

:Fame Factor Definition

To keep inputs consistent, use this rough scale:
- f = 1.0: world-famous landmark (e.g. The Burj Khalifa)
- f = 0.3: regionally famous tower
- f = 0.05: ordinary skyscraper with limited recognition

The implication:

High construction cost can only be recovered if fame-adjusted net cashflow, Rf - C, is strong. Because only one tower can be 'the tallest' at a time, most cities cannot sustain that level of attention, making the payback both slower and riskier.

Sensitivity Analysis:

The program tests a stress case where fame drops by 20% after a new taller building appears:
- f_new = 0.8f
- y_new = e / (Rf_new - C)

This shows how a loss of attention can delay the break-even or even remove it entirely.

Build and Run:

Compile:

g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o calculator

Run:

./calculator

Critical Assumptions and Limitations:

The following simplications are drastic but intentional: the model is for intuition, not a full finance evaluation.

- Revenue and operating cost are treated as constant over time.
- Competition is modeled as an immediate 20% fame drop while real competition is gradual.
- Many other factors are not addressed, including, financing, interest rates, inflation, etc.