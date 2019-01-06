package data;

import exceptions.ConnException;

import java.sql.ResultSet;
import java.sql.SQLException;

import static data.BuildingType.full;
import static data.BuildingType.normal;
import static exceptions.ConnException.ErrorTypes.hacker;
import static mains.Model.isHacker;

/**
 * Class representing a teacher information in SQL database, inherited from class Person.
 * @author Wojciech Sitek
 * @version 1.0
 * @since 2018-06-03
 * @see Person
 */
public class Teacher extends Person {
    /**
     * Copying class constructor. Admin defaultly set to false.
     * @param mailN value checked by {@link mains.Model#isHacker(String)} method, copied to private field {@link Person#mail}.
     * @param passN value checked by {@link mains.Model#isHacker(String)} method, copied to private field {@link Person#pass}.
     * @param nameN value checked by {@link mains.Model#isHacker(String)} method, copied to private field {@link Person#name}.
     * @throws ConnException thrown when there is hacking possibility (see method {@link mains.Model#isHacker(String)}).
     */
    public Teacher(String mailN, String passN, String nameN) throws ConnException {
        if(isHacker(mailN) || isHacker(passN) || isHacker(nameN)){
            throw new ConnException(hacker);
        }
        mail = mailN;
        pass = passN;
        name = nameN;
        admin = false;

    }

    /**
     * Main constructor of the class, taking information from
     * @param result {@link java.sql.ResultSet} value, keeping result of SQL query with teacher information.
     * @param buildingType {@link BuildingType} enum value, indicating way of constructing: either with going
     *                                          to next rows of ResultSet, or omitting it.
     * @throws SQLException thrown because of sudden error in connection with SQL database or error in information.
     */
    public Teacher (ResultSet result, BuildingType buildingType) throws SQLException {
        if(buildingType==full){
            group = new Group(result, full);
        }
        else if(buildingType==normal){
            result.next();
        }
        id = result.getInt("id");
        mail = result.getString("mail");
        pass = result.getString("pass");
        name = result.getString("name");
        admin = result.getBoolean("admin");

    }

    /**
     * Private boolean value, indicating if teacher is a system administrator. Unchangable after constructing object.
     */
    private boolean admin;

    /**
     * Get method for "admin" private field
     * @return {@link Teacher#admin}.
     */
    public boolean isAdmin(){return admin;}
}
