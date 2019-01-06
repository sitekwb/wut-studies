package data;

import sun.util.calendar.Gregorian;

import java.sql.Date;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.GregorianCalendar;

/**
 * Class, which objects keep set of data about student's attendance.
 * @author Wojciech Sitek
 * @version 1.0
 * @since 2018-06-03
 * @see Student
 */
public class Attendance {

    /**
     * Date of attendance taking
     */
    private Date date;
    /**
     * Bool indicating if student was present or no
     */
    private boolean present;
    /**
     * Id of attendance record from sql database
     */
    private int id;

    /**
     * Copying constructor
     * @param d date of taking attendance
     * @param isPresent bool giving information, whether student was present or no
     */
    public Attendance(Date d, boolean isPresent){
        date = d;
        present = isPresent;
    }
    public Attendance(int ids, Date d, boolean isPresent){
        id = ids;
        date = d;
        present = isPresent;
    }

    /**
     * Get method for attendance id
     * @return {@link #id}
     */
    public int getId(){
        return id;
    }

    /**
     * Get method for date
     * @return {@link data.Attendance#date}, private object of class Attendance
     */
    public Date getDate(){
        return date;
    }

    /**
     * Get method for day of week of class
     * @return day of week, which is taken from {@link #date}
     */
    public String getDay(){
        DateFormat format2=new SimpleDateFormat("EEEE");
        return format2.format(date);
    }
    /**
     * Get method for present
     * @return {@link data.Attendance#present}, private object of class Attendance
     */
    public boolean isPresent() {
        return present;
    }

    /**
     * Method setting value of field "present" as given
     * @param b bool parameter, to which is set class field present
     */
    public void setPresent(boolean b){
        present = b;
    }

    /**
     * Set method for date
     * @param d date, that is set in this method
     */
    public void setDate(Date d){
        date = d;
    }
}
