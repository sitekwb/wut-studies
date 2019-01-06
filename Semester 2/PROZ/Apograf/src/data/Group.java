package data;

import mains.Model;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Time;

import static data.BuildingType.*;


/**
 * Class representing SQL table data (Classes), keeping detail information about group of students and teachers.
 * @author Wojciech Sitek
 * @version 1.0
 * @since 2018-06-03
 */
public class Group {
    /**
     * Id represents primary key field in SQL table, unique for each group
     */
    private int id;

    /**
     * Get method for private field id.
     * @return Integer value of {@link Group#id}.
     */
    public int getId(){
        return id;
    }

    /**
     * Set method, setting given value as {@link Group#id}.
     * @param groupId integer, which is set to a private field
     */
    public void setId(int groupId){
        id = groupId;
    }


    /**
     * Name of group.
     */
    private String name;

    /**
     * Get method for {@link Group#name}.
     * @return String value of {@link Group#name}.
     */
    public String getName(){
        return name;
    }

    /**
     * Private integer, representing day of week. It takes values from 1 to 7 and 1=Monday.
     */
    private int day;

    /**
     * Public get method for private field {@link Group#day}.
     * @return value from 0 to 6, indicating day of week. 0=Monday.
     */
    public int getDayId(){
        return day-1;
    }

    /**
     * Private fields {@link Group#start_hour} and {@link Group#finish_hour} of deprecated type Time (but corresponding with SQL database),
     * keeping information about time of lessons in Group object.
     */
    private Time start_hour, finish_hour;

    /**
     * Set method for private fields {@link Group#start_hour} and {@link Group#finish_hour}.
     * @param time String parameter of wanted format hh:mm-hh:mm,
     *             indicating {@link Group#start_hour}-{@link Group#finish_hour}.
     * @throws Exception when parameter is in wrong format, then {@link java.sql.Time} constructor throws Exception,
     *                   which stops further processes.
     */
    private void setTime(String time)throws Exception{
        start_hour = new Time(Integer.parseInt(time.substring(0,2)), Integer.parseInt(time.substring(3,5)),0);
        finish_hour = new Time(Integer.parseInt(time.substring(6,8)), Integer.parseInt(time.substring(9,11)),0);
    }

    /**
     * Get method for start_hour.
     * @return {@link Group#start_hour} of type {@link java.sql.Time}.
     */
    public Time getStartHour(){ return start_hour; }
    /**
     * Get method for finish_hour.
     * @return {@link Group#finish_hour} of type {@link java.sql.Time}.
     */
    public Time getFinishHour(){ return finish_hour; }

    /**
     * Public get method for time: {@link Group#start_hour} and {@link Group#finish_hour}.
     * @return String format of time of lessons in this group to print in view.
     */
    public String getTime(){
        String value = String.format("%02d",start_hour.getHours())+":"+
                String.format("%02d",start_hour.getMinutes())+"-"+
                String.format("%02d",finish_hour.getHours())+":"+
                String.format("%02d",finish_hour.getMinutes());
        return value;
    }

    public static String getDay(int day){
        switch(day){
            case 1:
                return "Monday";
            case 2:
                return "Tuesday";
            case 3:
                return "Wednesday";
            case 4:
                return "Thursday";
            case 5:
                return "Friday";
            case 6:
                return "Saturday";
            case 7: default:
                return "Sunday";
        }
    }

    /**
     * Get method for time, giving full {@link java.lang.String} information about day and time of lessons in this group.
     * @return String format of day of week concatenated with return of time of start and finish {@link Group#getTime()}.
     */
    public String getSchedule(){
        String value = getDay(day);
        value+=" "+getTime();
        return value;
    }

    /**
     * Main constructor of the class, taking information from
     * @param result {@link java.sql.ResultSet} value, keeping result of SQL query with group information.
     * @param buildingType {@link BuildingType} enum value, indicating way of constructing: either with going
     *                                         to next rows of ResultSet, or omitting it.
     * @throws SQLException thrown because of sudden error in connection with SQL database or error in information.
     */
    public Group(ResultSet result, BuildingType buildingType) throws SQLException {
        if(buildingType== normal){
            result.next();
        }
        id = result.getInt("Classes.id");
        name = result.getString("Classes.name");
        day = result.getInt("Classes.day");
        start_hour = result.getTime("Classes.start_hour");
        finish_hour = result.getTime("Classes.finish_hour");
    }

    /**
     * Class constructor taking only necessary information to object: {@link Group#id} and {@link Group#name}.
     * @param result  {@link java.sql.ResultSet} value, keeping result of SQL query with group information.
     * @param small no matter the value of this bool parameter, it indicates this type of constructor.
     * @throws SQLException thrown because of sudden error in connection with SQL database or error in information.
     */
    public Group(ResultSet result, boolean small) throws SQLException {
        result.next();
        id = result.getInt("id");
        name = result.getString("name");
    }

    /**
     * Class constructor setting only {@link Group#id} and {@link Group#name} values from
     * @param tid integer setting private field id
     * @param tname {@link java.lang.String}, setting private field name
     * @throws SQLException thrown because of sudden error in connection with SQL database or error in information.
     */
    public Group(int tid, String tname)throws SQLException{
        if(Model.isHacker(tname)){
            throw new SQLException();
        }
        id = tid;
        name = tname;
    }

    /**
     * Class constructor initialising all values in class by copying.
     * @param groupName initialises {@link Group#name}, after checking if value doesn't containt forbidden hacking
     *                  characters like ' or " by method {@link mains.Model#isHacker(String)}.
     * @param groupDay initialises {@link Group#day}, after checking if value is corresponding class constraints.
     * @param time initialises {@link Group#start_hour} and {@link Group#finish_hour}
     *             by public method {@link Group#setTime(String)}, which checks if data is correct.
     * @throws Exception in case of incorrect or hacking data this exception is thrown
     */
    public Group(String groupName, int groupDay, String time)throws Exception {
        if(Model.isHacker(groupName) || groupDay<1 || groupDay>7){
            throw new Exception();
        }
        name = groupName;
        day = groupDay;
        setTime(time);
    }


}
