package data;

import exceptions.ConnException;

import java.sql.ResultSet;
import java.sql.SQLException;
import static data.BuildingType.*;
import static exceptions.ConnException.ErrorTypes.hacker;
import static mains.Model.isHacker;

/**
 * Class representing a student information in SQL database, inherited from class Person.
 * @see Person
 * @author Wojciech Sitek
 * @version 1.0
 * @since 2018-06-03
 */
public class Student extends Person{
    /**
     * Copying class constructor
     * @param mailN value checked by {@link mains.Model#isHacker(String)} method, copied to private field {@link Person#mail}.
     * @param passN value checked by {@link mains.Model#isHacker(String)} method, copied to private field {@link Person#pass}.
     * @param nameN value checked by {@link mains.Model#isHacker(String)} method, copied to private field {@link Person#name}.
     * @param student_idN value copied to private field {@link Student#student_id}.
     * @param genGroupN  value checked by {@link mains.Model#isHacker(String)} method, copied to private field {@link Student#genGroup}.
     * @throws ConnException thrown when there is hacking possibility (see method {@link mains.Model#isHacker(String)}).
     */
    public Student(String mailN, String passN, String nameN, int student_idN, String genGroupN) throws ConnException{
        if(isHacker(mailN) || isHacker(passN) || isHacker(nameN)  || isHacker(genGroupN)){
            throw new ConnException(hacker);
        }
        mail = mailN;
        pass = passN;
        name = nameN;
        student_id = student_idN;
        genGroup = genGroupN;
        if(genGroup==null){
            genGroup = "";
        }

    }

    /**
     * Main constructor of the class, taking information from
     * @param result {@link java.sql.ResultSet} value, keeping result of SQL query with student information.
     * @param buildingType {@link BuildingType} enum value, indicating way of constructing: either with going
     *                                          to next rows of ResultSet, or omitting it.
     * @throws SQLException thrown because of sudden error in connection with SQL database or error in information.
     */
    public Student (ResultSet result, BuildingType buildingType) throws SQLException{
        if(buildingType==full){
            group = new Group(result, full);
        }
        else if(buildingType==normal){
            result.next();
        }
        id = result.getInt("Students.id");
        mail = result.getString("Students.mail");
        pass = result.getString("Students.pass");
        name = result.getString("Students.name");
        student_id = result.getInt("Students.student_id");
        genGroup = result.getString("Students.gen_class");
        if(genGroup==null){
            genGroup = "";
        }
    }

    /**
     * Class constructor taking only necessary information to object: {@link Person#id}, {@link Person#name} and {@link Student#attendance}
     * @param result  {@link java.sql.ResultSet} value, keeping result of SQL query with student information.
     * @param attendanceFlag if is true, {@link Student#attendance} is initialised, else not.
     * @throws SQLException thrown because of sudden error in connection with SQL database or error in information.
     */
    public Student(ResultSet result, boolean attendanceFlag) throws SQLException{
        result.next();
        id = result.getInt("Students.id");
        name = result.getString("Students.name");
        genGroup="";
        if(attendanceFlag){
            attendance = new Attendance(result.getInt("Attendance.id"), result.getDate("date"), result.getBoolean("present"));
        }
    }

    /**
     * Private field student_id, integer without constraints, in SQL database must be unsigned, so sending minus value
     * to SQL database may end {@link java.sql.SQLException}.
     */
    private int student_id;

    /**
     * Set method for student id.
     * @param studentID sets private field {@link Student#student_id}.
     */
    public void setStudentID(int studentID){
        student_id = studentID;
    }

    /**
     * Get method for student id.
     * @return String value of {@link Student#student_id}.
     */
    public String getStudentID(){
        return String.valueOf(student_id);
    }


    /**
     * Private String genGroup. It's a description of student's place in university: semester or degree.
     * Shouldn't contain forbidden characters like ' or ", which may hack SQL database.
     */
    private String genGroup;

    /**
     * Get method for genGroup.
     * @return {@link Student#genGroup}.
     */
    public String getGenGroup(){
        return genGroup;
    }

    /**
     * Set method for genGroup. Checking hacking possibilities.
     * @param g value set to {@link Student#genGroup}
     * @throws ConnException {@link ConnException}, informs about possible hacking try.
     */
    public void setGenGroup(String g) throws ConnException{
        if(isHacker(g)){
            throw new ConnException(hacker);
        }
        genGroup = g;
    }

    /**
     * Private field attendance, not always initialised, of type {@link Attendance}.
     */
    private Attendance attendance;

    /**
     * Set method for attendance field.
     * @param at copied value to {@link Student#attendance}.
     */
    public void setAttendance(Attendance at){
        attendance = at;
    }

    /**
     * Get method for attendance private field.
     * @return {@link Student#attendance}.
     */
    public Attendance getAttendance(){
        return attendance;
    }


}
