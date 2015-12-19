import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.TreeSet;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
	private static final Pattern PATTERN = Pattern.compile("(\\w+)\\ =>\\ (\\w+)");

	private static String str = "CRnCaSiRnBSiRnFArTiBPTiTiBFArPBCaSiThSiRnTiBPBPMgArCaSiRnTiMgArCaSiThCaSiRnFArRnSiRnFArTiTiBFArCaCaSiRnSiThCaCaSi"
			+ "RnMgArFYSiRnFYCaFArSiThCaSiThPBPTiMgArCaPRnSiAlArPBCaCaSiRnFYSiThCaRnFArArCaCaSiRnPBSiRnFArMgYCaCaCaCaSiThCaCaSiAlArCaCaSiRnPBSiAlAr"
			+ "BCaCaCaCaSiThCaPBSiThPBPBCaSiRnFYFArSiThCaSiRnFArBCaCaSiRnFYFArSiThCaPBSiThCaSiRnPMgArRnFArPTiBCaPRnFArCaCaCaCaSiRnCaCaSiRnFYFArFArB"
			+ "CaSiThFArThSiThSiRnTiRnPMgArFArCaSiThCaPBCaSiRnBFArCaCaPRnCaCaPMgArSiRnFYFArCaSiThRnPBPMgAr";

	private static List<Replacement> l = new ArrayList<Replacement>();

	public static void main(String[] args) throws IOException, InterruptedException {

		List<String> lines = Files.readAllLines(Paths.get("in"));
		for (String line : lines) {
			Matcher matcher = PATTERN.matcher(line);
			if (matcher.matches()) {
				l.add(new Replacement(matcher.group(1), matcher.group(2)));

			}
		}

		TreeSet<Node> openSet = new TreeSet<Node>();
		TreeSet<Node> closedSet = new TreeSet<Node>();

		openSet.add(new Node(str, 0, heur(str, "e")));

		while (!openSet.isEmpty()) {
			Node current = openSet.first();

			if (current.getS().equals("e")) {
				System.out.println(current.getCost());
				System.exit(0);
			}

			openSet = remove(current, openSet);
			
			if (!contains(current, closedSet)) {
				closedSet.add(current);
			}

			for (Replacement rep : l) {
				int offset = 0;
				while ((offset = current.getS().indexOf(rep.getRepee(), offset)) >= 0) {
					int length = rep.getRepee().length();
					Node neightbor = new Node(replaceAtOffSet(current.getS(), rep.getRep(), offset, length), Integer.MAX_VALUE, Integer.MAX_VALUE);
					offset += length;

					if (contains(neightbor, closedSet)) {
						continue;
					}

					int ncost = current.getCost() + 1;

					if (!contains(neightbor, openSet)) {
						openSet.add(neightbor);
					} else if (ncost > neightbor.getCost()) {
						continue;
					}

					neightbor.setCost(ncost);
					neightbor.setScore(ncost + heur(neightbor.getS(), "e"));
				}
			}
		}
	}

	private static TreeSet<Node> remove(Node n, TreeSet<Node> set) {
		TreeSet<Node> result = new TreeSet<Node>();
		for (Node node : set) {
			if (!n.getS().equals(node.getS())) {
				result.add(node);
			}
		}
		return result;
	}
	
	private static boolean contains(Node n, TreeSet<Node> set) {
		for (Node node : set) {
			if (n.getS().equals(node.getS())) {
				return true;
			}
		}
		return false;
	}

	private static int heur(String str2, String string) {
		return str2.length() - string.length();
	}

	public static String replaceAtOffSet(String str, String replace, int offset, int repLength) {
		return str.substring(0, offset) + replace + str.substring(offset + repLength);
	}

	public static class Node implements Comparable<Node> {
		private String s;
		private int cost;
		private int score;

		Node(String s, int cost, int score) {
			this.s = s;
			this.cost = cost;
			this.score = score;
		}

		@Override
		public int hashCode() {
			return s.hashCode();
		}

		@Override
		public boolean equals(Object obj) {
			return s.equals(((Node) obj).getS());
		}

		@Override
		public int compareTo(Node o) {
			return o.getS().equals(this.getS()) ? 0 : (o.score < this.score ? 1 : -1);
		}

		public String getS() {
			return s;
		}

		public void setS(String s) {
			this.s = s;
		}

		public int getCost() {
			return cost;
		}

		public void setCost(int cost) {
			this.cost = cost;
		}

		public int getScore() {
			return score;
		}

		public void setScore(int score) {
			this.score = score;
		}
	}

	public static class Replacement implements Comparable<Replacement> {

		private String rep;
		private String repee;

		Replacement(String rep, String repee) {
			this.rep = rep;
			this.repee = repee;
		}

		public String getRep() {
			return rep;
		}

		public String getRepee() {
			return repee;
		}

		@Override
		public int compareTo(Replacement o) {
			return (o.getRepee().length() > this.getRepee().length() ? 1 : -1);
		}
	}
}

