package game;

import java.util.*;
import static game.InOutUtils.readStringsFromInputStream;
import static game.ProcessUtils.UTF_8;

/**
 * Main samplegame class.
 */
public class Main {

    public static void main(String[] args) {
        List<String> input = readStringsFromInputStream(System.in, UTF_8);
        if(!input.isEmpty()){
            Round round = new Round(input);
            printMovingGroups(makeMove(round));
        }
        System.exit(0);
    }

    private static List<MovingGroup> makeMove(Round round) {
        List<MovingGroup> movingGroups = new ArrayList<>();
        List<Planet> planet_info = round.getPlanets();
        // Место для Вашего кода.
        for (int i = 1; i < planet_info.size(); i++) {
            Planet current_planet = planet_info.get(i);
            if (current_planet.getOwnerTeam() == -1 && current_planet.getId() < 5) {
                movingGroups.add(new MovingGroup(round.getTeamId(), current_planet.getId(), current_planet.getPopulation() + 1));
            }
        }
        System.out.println();
        MovingGroup gr_1 = new MovingGroup();
        movingGroups.add(gr_1);
        return movingGroups;
    }

    private static void printMovingGroups(List<MovingGroup> moves) {
        System.out.println(moves.size());
        moves.forEach(move -> System.out.println(move.getFrom() + " " + move.getTo() + " " + move.getCount()));
    }

}
