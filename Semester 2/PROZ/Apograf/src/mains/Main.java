package mains;

import mains.controllers.Controller;

/**
 * Class containing main method
 */
public class Main {
    /**
     * Main method, initialising main {@link Controller} and, as its parameter giving {@link Model},
     * from model of programming MVC.
     * @param args unused arguments
     */
    public static void main(String [] args){

        Controller controller = new Controller(new Model());
    }
}
