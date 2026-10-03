GigiQuant - Portfolio Manager

Overview

This project is built around a series of interview-style tasks for a portfolio manager role at a fictional company called "GigiQuant". The main goal is to apply classic data structures (like linked lists, stacks, queues, binary trees, and graphs) and custom algorithms to solve practical financial problems.

(All requirements and implementation details are based on the ProiectPA_GigiQ.pdf reference document).

What's inside

Task 1: Sharpe Ratio

Goal: Evaluate a portfolio's performance and profitability relative to the risk taken.

Under the hood: I used singly linked lists to keep track of daily portfolio values and returns. Based on these, the algorithm calculates the average return and volatility (standard deviation) to figure out the Sharpe Ratio, truncated to 3 decimal places.

Task 3: Portfolio Diversification

Goal: Optimize a portfolio by pairing volatile stocks with their exact opposites to build a stable, balanced structure.

Under the hood: Daily price movements (ups and downs) are stored recursively in a binary tree. By traversing this tree, the algorithm finds the "mirror" of each stock to effectively diversify the portfolio.

Task 4: Markov Chains

Goal: Calculate the odds of a stock moving from a starting price to a specific target price over a set number of days.

Under the hood: Prices are grouped into fixed-size intervals (K), with each interval acting as a node in a graph. The program traverses the graph day by day to calculate the final probability, outputting the result as an irreducible fraction.

Bonus: Financial API Integration

Goal: Hook the project up to real-time external data.

Under the hood: I used libcurl to make HTTP requests to the Yahoo Finance API and cJSON to parse the incoming data. The core function (get_open_prices) pulls opening prices for a specific stock ticker (e.g., AAPL) so they can be fed directly into the Task 1 calculations.
