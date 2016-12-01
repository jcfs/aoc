package aoc;

import java.util.ArrayList;
import java.util.List;

public class Day21 {
  static boolean fight(int php, int pd, int pa, int bhp, int bd, int ba) {
    while (php > 0 && bhp > 0) {
      bhp -= Math.max((pd - ba), 1);
      php -= Math.max((bd - pa), 1);
    }
    return bhp <= 0;
  }

  public static void main(String[] args) {
    List<Weapon> weapons = new ArrayList<Weapon>();
    List<Armor> armors = new ArrayList<Armor>();
    List<Ring> rings = new ArrayList<Ring>();

    weapons.add(new Weapon(8, 4));
    weapons.add(new Weapon(10, 5));
    weapons.add(new Weapon(25, 6));
    weapons.add(new Weapon(40, 7));
    weapons.add(new Weapon(74, 8));

    armors.add(new Armor(0, 0));
    armors.add(new Armor(13, 1));
    armors.add(new Armor(31, 2));
    armors.add(new Armor(53, 3));
    armors.add(new Armor(75, 4));
    armors.add(new Armor(102, 5));

    rings.add(new Ring(1, 25, 1, 0));
    rings.add(new Ring(2, 50, 2, 0));
    rings.add(new Ring(3, 100, 3, 0));
    rings.add(new Ring(4, 20, 0, 1));
    rings.add(new Ring(5, 40, 0, 2));
    rings.add(new Ring(6, 80, 0, 3));
    rings.add(new Ring(7, 0, 0, 0));
    rings.add(new Ring(8, 0, 0, 0));

    int min = Integer.MAX_VALUE;
    int max = Integer.MIN_VALUE;
    for (Weapon weapon : weapons) {
      for (Armor armor : armors) {
        for (Ring ring1 : rings) {
          for (Ring ring2 : rings) {
            if (!ring1.equals(ring2)) {
              boolean fight = fight(100, weapon.dmg + ring1.dmg + ring2.dmg, armor.armor + ring1.armor + ring2.armor, 103, 9, 2);
              int cost = weapon.cost + ring1.cost + ring2.cost + armor.cost;
              if (fight) {
                min = Math.min(cost, min);
              } else {
                max = Math.max(cost, max);
              }
            }
          }
        }
      }
    }
    System.out.println("min: " + min + " " + "max: " + max);
  }

  private static class Weapon {
    public int cost;
    public int dmg;

    public Weapon(int cost, int dmg) {
      this.cost = cost;
      this.dmg = dmg;
    }
  }

  private static class Armor {
    public int cost;
    public int armor;

    public Armor(int cost, int armor) {
      this.cost = cost;
      this.armor = armor;
    }
  }

  private static class Ring {
    public int cost;
    public int dmg;
    public int armor;
    public int index;

    @Override
    public boolean equals(Object obj) {
      return this.index == ((Ring) obj).index;
    }

    public Ring(int index, int cost, int dmg, int armor) {
      this.index = index;
      this.cost = cost;
      this.armor = armor;
      this.dmg = dmg;
    }
  }
}

