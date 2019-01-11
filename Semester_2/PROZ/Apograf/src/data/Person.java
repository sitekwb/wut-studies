package data;

import exceptions.ConnException;

import java.sql.SQLException;

import static exceptions.ConnException.ErrorTypes.hacker;
import static mains.Model.isHacker;

/**
 * Class representing set of data copied from SQL database or created locally, necessary to service program,
 * regarding Person. This abstract class is inherited by {@link Student} and {@link Teacher}, because in the program each
 * person is either a student or a teacher.
 * @author Wojciech Sitek
 * @version 1.0
 * @since 2018-06-03
 */
public abstract class Person {
    /**
     * String value which has both teacher and student, necessary for database and logging service.
     * These field shouldn't contain 'hacking' characters like ' and ", which could hack the database.
     */
    protected String mail;
    /**
     * Get method for private mail field.
     * @return {@link Person#mail}
     */
    public String getMail(){
        return mail;
    }

    /**
     * Set method for private field mail, checked anti-hacking by static method {@link mains.Model#isHacker(String)}.
     * @param m string value of mail, not checked (it can be not an email as well - app doesn't send any mails)
     * @throws ConnException {@link ConnException}, exception, keeping information about hacking try (in inside enum).
     */
    public void setMail(String m)throws ConnException {
        if(isHacker(m)){
            throw new ConnException(hacker);
        }
        mail = m;
    }
    /**
     * String value which has both teacher and student, necessary for database and logging service.
     * These field shouldn't contain 'hacking' characters like ' and ", which could hack the database.
     */
    protected String pass;

    /**
     * Set method for protected field pass, checked anti-hacking by static method {@link mains.Model#isHacker(String)}.
     * @param p string value of {@link Person#pass}word, not checked (it can be not an email as well - app doesn't send any mails)
     * @throws ConnException {@link ConnException}, exception, keeping information about hacking try (in inside enum).
     */
    public void setPass(String p) throws ConnException{
        if(isHacker(p)){
            throw new ConnException(hacker);
        }
        pass = p;
    }

    /**
     * Get method for password.
     * @return {@link Person#pass}
     */
    public String getPass(){ return pass; }

    /**
     * String value which have both teacher and student, necessary for identifying person in program.
     * These field shouldn't contain 'hacking' characters like ' and ", which could hack the database.
     */
    protected String name;
    /**
     * Set method for protected field name, checked anti-hacking by static method {@link mains.Model#isHacker(String)}.
     * @param n string value of {@link Person#name}.
     * @throws ConnException {@link ConnException}, exception, keeping information about hacking try (in inside enum).
     */
    public void setName(String n)throws ConnException{
        if(isHacker(n)){
            throw new ConnException(hacker);
        }
        name = n;
    }

    /**
     * Get method for name.
     * @return {@link Person#name}.
     */
    public String getName(){
        return name;
    }
    /**
     * Not always initialised field of type {@link Group}. Because of the fact that one person can have many groups,
     * this field is used only, when we want to print joined table of people and groups.
     */
    protected Group group;

    /**
     * Get method for field group
     * @return {@link Person#group}, sometimes can be null, when field is not initialised.
     */
    public Group getGroup(){
        return group;
    }

    /**
     * Unique primary key of table Students or Teachers in SQL, of type Integer.
     */
    protected int id;


    /**
     * Get method for id
     * @return {@link Person#id}
     */
    public int getId(){
        return id;
    }
}
