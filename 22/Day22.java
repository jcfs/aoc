package aoc;

import java.util.ArrayList;
import java.util.List;

public class Day22 {

  private static int min = Integer.MAX_VALUE;
  private static List<String> availableSpells = new ArrayList<String>();

  static int simmulate(List<String> spellsArray, boolean hardmode) throws InstantiationException, IllegalAccessException, ClassNotFoundException {
    GameState gameState = new GameState();
    int manaSpent = 0;

    for (String spellStr : spellsArray) {
      Spell spell = (Spell) Class.forName(spellStr).newInstance();

      if (hardmode) {
        gameState.php--;
      }

      if (gameState.php <= 0) {
        return -1;
      }

      evaluateEffects(gameState);
      if (canCastEffect(gameState, spell)) {
        return -1;
      }

      if (gameState.bhp <= 0) {
        min = Math.min(min, manaSpent);
        return 1;
      }

      gameState.pmana -= spell.cost;

      if (gameState.php <= 0 || gameState.pmana <= 0) {
        return -1;
      }

      manaSpent += spell.cost;
      evaluateSpell(spell, gameState);

      // Start of boss turn
      evaluateEffects(gameState);

      if (gameState.bhp <= 0) {
        min = Math.min(min, manaSpent);
        return 1;
      }

      gameState.php -= Math.max(1, gameState.bdmg - gameState.parmor);
    }

    return 0;
  }

  private static boolean canCastEffect(GameState gameState, Spell spell) {
    return spell instanceof Poison && gameState.poisonTimer > 0 || spell instanceof Recharge && gameState.rechargeTimer > 0
      || spell instanceof Shield && gameState.shieldTimer > 0;
  }

  private static int evaluateSpell(Spell spell, GameState gameState) {
    if (spell instanceof Poison) {
      gameState.poisonTimer = 6;
    }

    if (spell instanceof Shield) {
      gameState.shieldTimer = 6;
    }

    if (spell instanceof Recharge) {
      gameState.rechargeTimer = 5;
    }

    if (spell instanceof Missile) {
      Missile mis = (Missile) spell;
      gameState.bhp -= mis.dmg;
    }

    if (spell instanceof Drain) {
      Drain mis = (Drain) spell;
      gameState.bhp -= mis.dmg;
      gameState.php += mis.heal;
    }

    return 0;
  }

  private static void evaluateEffects(GameState gameState) {
    if (gameState.poisonTimer > 0) {
      gameState.bhp -= 3;
      gameState.poisonTimer--;
    }

    if (gameState.rechargeTimer > 0) {
      gameState.pmana += 101;
      gameState.rechargeTimer--;
    }

    if (gameState.shieldTimer > 0) {
      gameState.parmor = 7;
      gameState.shieldTimer--;
      if (gameState.shieldTimer == 0) {
        gameState.parmor = 0;
      }
    }
  }

  static void doSimulation(List<String> current, boolean hardmode) throws InstantiationException, IllegalAccessException, ClassNotFoundException {
    int result = simmulate(current, hardmode);

    if (current.size() > 9) {
      return;
    }

    if (result != 0) {
      return;
    }

    for (int i = 0; i < availableSpells.size(); i++) {
      current.add(availableSpells.get(i));
      doSimulation(current, hardmode);
      current.remove(current.size() - 1);
    }
  }

  public static void main(String[] args) throws InstantiationException, IllegalAccessException, ClassNotFoundException {

    availableSpells.add(Poison.class.getName());
    availableSpells.add(Shield.class.getName());
    availableSpells.add(Recharge.class.getName());
    availableSpells.add(Missile.class.getName());
    availableSpells.add(Drain.class.getName());

    min = Integer.MAX_VALUE;
    doSimulation(new ArrayList<String>(), false);
    System.out.println(min);

    min = Integer.MAX_VALUE;
    doSimulation(new ArrayList<String>(), true);
    System.out.println(min);
  }

  public static class GameState {
    public int php = 50;
    public int pmana = 500;
    public int bhp = 55;
    public int bdmg = 8;
    public int parmor = 0;
    public int poisonTimer = 0;
    public int rechargeTimer = 0;
    public int shieldTimer = 0;
  }

  private static abstract class Spell {
    public int cost;
  }

  public static class Poison extends Spell {
    public int dot = 3;
    public int timer = 6;

    public Poison() {
      this.cost = 173;
    }
  }

  public static class Recharge extends Spell {
    int timer = 5;
    int mana = 101;

    public Recharge() {
      this.cost = 229;
    }
  }

  public static class Shield extends Spell {
    int timer = 6;
    int armor = 7;

    public Shield() {
      this.cost = 113;
    }
  }

  public static class Drain extends Spell {
    int dmg = 2;
    int heal = 2;

    public Drain() {
      this.cost = 73;
    }
  }

  public static class Missile extends Spell {
    int dmg = 4;

    public Missile() {
      this.cost = 53;
    }
  }
}
