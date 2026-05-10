If megatall skyscrapers are so profitable and recognizable, why doesn't every city build one? This model will answer why.

Model structure:

Net profit after y years:

p = y * (R*f - C) * (1 - t) - e

Variables:
- e: construction cost (USD)
- R: annual revenue projection (USD)
- f: fame multiplier
- C: annual operating cost (USD)
- t: effective tax rate (0.0 to 0.99)
- y: years since opening

Break-even condition p = 0:

y = e / ((R*f - C) * (1 - t))

If (R*f - C) * (1 - t) <= 0, the project will never break even in this model.

Fame Factor Definition:

To keep inputs consistent, use this rough scale:
- f = 1.0: world-famous landmark (e.g. The Burj Khalifa)
- f = 0.3: regionally famous tower
- f = 0.05: ordinary skyscraper with limited recognition

The implication:

High construction cost can only be recovered if after-tax, fame-adjusted net cashflow, (R*f - C) * (1 - t), is strong. Because only one tower can be 'the tallest' at a time, most cities cannot sustain that level of attention, making the payback both slower and riskier. Taxation further extends break-even timelines, especially for high-revenue projects.

Sensitivity Analysis:

The program tests two stress cases:

Case 1 — Fame shock (new taller building appears):
- f_new = 0.8f
- y_new = e / ((R*f_new - C) * (1 - t))

Case 2 — Cost overrun (operating costs rise 15%):
- C_new = 1.15C
- y_new = e / ((R*f - C_new) * (1 - t))

Both cases show how external shocks can delay break-even or remove it entirely.

Build and Run:

Compile:

g++ -std=c++23 -Wall -Wextra -pedantic main.cpp -o calculator

Run:

./calculator

Critical Assumptions and Limitations:

The following simplifications are drastic but intentional: the model is for intuition, not a full finance evaluation.

- Revenue, operating cost, and tax rate are treated as constant over time.
- Competition is modeled as an immediate 20% fame drop while real competition is gradual.
- Cost overrun is modeled as an immediate 15% increase in operating cost.
- Many other factors are not addressed, including financing, interest rates, inflation, etc.