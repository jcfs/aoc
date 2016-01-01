
public class Day24 {

	static final boolean PART2 = false;

	static int totalWeight = 0;
	static int w[] = { 1, 2, 3, 5, 7, 13, 17, 19, 23, 29, 31, 37, 41, 43, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113 };
	static boolean v[] = new boolean[w.length];

	static long min = Integer.MAX_VALUE;
	static int minCount = Integer.MAX_VALUE;
	static boolean possible = false;

	static void divideGroupThree(int total, int current) {
		if (possible) {
			return;
		}

		if (total == totalWeight) {
			possible = true;
			return;
		}

		for (int i = current; i < w.length; i++) {
			if (!v[i] && total + w[i] <= totalWeight) {
				v[i] = true;
				divideGroupThree(total + w[i], i + 1);
				v[i] = false;
			}
		}
	}

	static void divideGroupTwo(int total, int current) {
		if (possible) {
			return;
		}

		if (total == totalWeight) {
			divideGroupThree(0, 0);
			return;
		}

		for (int i = current; i < w.length; i++) {
			if (!v[i] && total + w[i] <= totalWeight) {
				v[i] = true;
				divideGroupTwo(total + w[i], i + 1);
				v[i] = false;
			}
		}
	}

	static void divideGroupOne(int total, long qt, int count, int current) {
		if (total > totalWeight) {
			return;
		}

		if (total == totalWeight) {
			possible = false;

			if (PART2) {
				divideGroupTwo(0, 0);
			} else {
				divideGroupThree(0, 0);
			}
			
			if (possible) {
				if (count < minCount) {
					minCount = count;
					min = qt;
				} else if (count == minCount) {
					if (qt < min) {
						min = qt;
					}
				}
			}
		}

		for (int i = current; i < w.length; i++) {
			if (!v[i] && total + w[i] <= totalWeight) {
				v[i] = true;
				divideGroupOne(total + w[i], w[i] * qt, count + 1, i + 1);
				v[i] = false;
			}
		}
	}

	public static void main(String[] args) {
		for (int i = 0; i < w.length; i++) {
			totalWeight += w[i];
		}

		totalWeight /= PART2 ? 4 : 3;
		divideGroupOne(0, 1, 0, 0);
		System.out.printf("%d\n", min);
	}

}
