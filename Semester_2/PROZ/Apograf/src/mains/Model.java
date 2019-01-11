package mains;

import exceptions.ConnException;
import data.*;

import javax.swing.plaf.nimbus.State;
import java.sql.*;
import java.util.ArrayList;

import static exceptions.ConnException.ErrorTypes.*;


/**
 * Only class representing model from MVC, getting information from SQL database.
 * It connects only with controllers, not with view. All controllers have reference to model.
 * There is one object of this class created during all program instance, created in first line of {@link Main}.
 * @author Wojciech Sitek
 * @version 1.0
 * @since 2018-06-03
 */
public class Model {
    /**
     * Parameter type {@link java.sql.Connection}, established during logging or registering and being closed
     * after signing out. Almost all methods in this class use this parameter.
     */
    private Connection conn;

    /**
     * Public internal enum class, indicating which is the type of user, that has logged in.
     */
    public enum UserType {admin, student, teacher};
    /**
     * Private parameter of type {@link UserType}, keeping information about type of user: either admin, or student,
     * or teacher.
     */
    private UserType userType;
    /**
     * Parameter keeping the reference of person, that is logged in. It is either an instance of class {@link Student}
     * or of class {@link Teacher}.
     */
    private Person me;


    /**
     * <p>Method checks if mail and password are in the database and initialises {@link #userType} parameter.</p>
     * <p>Method checkUser gets information from the database tables (Teachers, Students and Admins)
     * and compares it with data given by user (mail and password). </p>
     * <p>Method implemented in this class method openConnection</p>
     *
     * @param mail            e-mail adress entered by user in the InitialView
     * @param enteredPassword pass entered by user in view
     * @return type of user (enum) - admin, teacher or student. On this depends type of downloaded data
     * and consequently view
     * @throws ConnException informs {@link init.InitController} module about type of error occuring
     *                       (connection with database, wrong mail, wrong password)
     * @throws SQLException  if the process of connection with database breaks, then this exception is thrown
     * @see #logIn(String, String)
     */
    UserType checkUser(String mail, String enteredPassword) throws ConnException, SQLException {
        String pass, query;
        ResultSet result;
        Statement statement = conn.createStatement();

        //STUDENT
        query = "SELECT pass FROM Students WHERE mail='" + mail + "' LIMIT 1;";

        result = statement.executeQuery(query);
        if (result.next()) {//if something was found
            pass = result.getString("pass");
            if (pass.equals(enteredPassword))
                return UserType.student;
            //if pass from database doesn't equal entered password
            throw new ConnException(wrongPass);
        }
        //TEACHER - checking if logging user is a teacher or admin
        query = "SELECT pass,admin FROM Teachers WHERE mail='" + mail + "' LIMIT 1;";
        result = statement.executeQuery(query);
        if (result.next()) {//if something was found
            pass = result.getString("pass");
            if (pass.equals(enteredPassword)) {
                if (result.getBoolean("admin")) {
                    return UserType.admin;
                }
                return UserType.teacher;
            }

            //if pass from database doesn't equal entered password
            throw new ConnException(wrongPass);
        }
        //if e-mail was not found in any database => throw not-existing exception
        throw new ConnException(notExitsting);
    }

    /**
     * Closes connection with database
     *
     * @throws SQLException if something goes wrong with closing connection, the exception is thrown
     * @see #signOut()
     */
    public void closeConnection() throws SQLException {
        if (conn != null && !conn.isClosed()) conn.close();
    }

    /**
     * Opens connection with database, initialising {@link Model#conn}.
     * @throws SQLException if something goes wrong with opening connection, the exception is thrown
     */
    private void openDatabaseConnection() throws SQLException {
        conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/apograf", "access", "xxxx");
    }

    /**
     * Logs in the user, given mail and password.
     * First checks if this user is a hacker by method {@link #isHacker(String)},
     * then opens database connection,
     * checks if this user exists by method {@link #checkUser(String, String)} and finally
     * gets from SQL tables information about student or teacher.
     * @param mail e-mail, unique in SQL tables, identifies user
     * @param pass checked by method {@link #checkUser(String, String)}, if is correct, cannot be hacking.
     * @throws ConnException if something goes wrong, this exception is thrown to {@link init.InitController}
     */
    public void logIn(String mail, String pass) throws ConnException {

        if (isHacker(mail) || isHacker(pass)) {
            throw new ConnException(hacker);
        }
        try {
            openDatabaseConnection();
            //check if user has given the right data
            userType = checkUser(mail, pass);
            //download personal data
            Statement statement = conn.createStatement();
            String query;
            switch (userType) {
                case teacher:
                    query = "SELECT * FROM Teachers WHERE mail='" + mail + "' LIMIT 1;";
                    me = new Teacher(statement.executeQuery(query), BuildingType.normal);
                    break;
                case admin:
                    query = "SELECT * FROM Teachers WHERE mail='" + mail + "' LIMIT 1;";
                    me = new Teacher(statement.executeQuery(query), BuildingType.normal);
                    break;
                case student:
                default:
                    query = "SELECT * FROM Students WHERE mail='" + mail + "' LIMIT 1;";
                    me = new Student(statement.executeQuery(query), BuildingType.normal);
            }
            statement.close();
        } catch (SQLException e) {
            throw new ConnException(err);
        }
    }

    /**
     * Checks if this type, which we want to add to Waiting table for administrator check, is just waiting
     * connected with this user, in table Waiting.
     * @param type String value, can be one of the types that can wait in database for admin check: name, student_id, etc.
     * @return returns true, if this value is just waiting in database and false if not
     * @throws SQLException if something goes wrong in connection with database.
     * @throws ConnException if something goes wrong with data given by user
     */
    private boolean isWaitingInDatabase(String type) throws SQLException, ConnException {
        if (isHacker(type)) {
            throw new ConnException(hacker);
        }
        ResultSet result;
        Statement statement = conn.createStatement();
        String query = "SELECT pass FROM Waiting WHERE mail='" +me.getMail() + "' AND type='"+type+"' LIMIT 1;";
        result = statement.executeQuery(query);
        if (result.next()) {
            statement.close();
            return true;
        }
        statement.close();
        return false;
    }

    /**
     * Checks if mail, that someone wants to occupy, isn't in database - in tables Teachers, Students or Waiting.
     * @param mail e-mail, which occurrence is checked in database. Cannot contain forbidden chars like '," or ;
     * @return returns true, if mail is just in one of these databases.
     * @throws SQLException if something goes wrong in connection with database.
     */
    private boolean isMailInDatabase(String mail)throws SQLException{
        ResultSet result;
        Statement statement = conn.createStatement();
        String query = "SELECT mail FROM Teachers WHERE mail='"+mail+"' LIMIT 1;";
        //TEACHERS - checking if there is mail existing in database

        result = statement.executeQuery(query);
        if(result.next()){
            return true; //mail is just in database
        }
        //STUDENTS
        query = "SELECT mail FROM Students WHERE mail='"+mail+"' LIMIT 1;";
        result = statement.executeQuery(query);
        if(result.next()){
            return true;
        }
        //WAITING
        query = "SELECT mail FROM Waiting WHERE mail='"+mail+"' LIMIT 1;";
        result = statement.executeQuery(query);
        if(result.next()){
            return true;
        }
        statement.close();
        return false;
    }

    /**
     * Tries to register new user, checking and taking his mail and password into Waiting table, waiting for
     * admin check.
     * @param mail e-mail that is first checked by method {@link #isHacker(String)},
     *             then by method {@link #isMailInDatabase(String)} and finally inserted into Waiting table.
     * @param pass e-mail that is first checked by method {@link #isHacker(String)} and then inserted into Waiting table
     *             together with mail.
     * @throws ConnException if something goes wrong with data given by user.
     */
    public void register(String mail, String pass)throws ConnException{
        if(isHacker(mail) || isHacker(pass)){
            throw new ConnException(hacker);
        }
        try {
            openDatabaseConnection();
            if(isMailInDatabase(mail)){
                throw new ConnException(existing);
            }
            //enter this mail and password into waiting
            Statement stmt=conn.createStatement();
            stmt.executeUpdate("INSERT INTO Waiting (mail, pass) VALUES ('"+mail+"', '"+pass+"');");
            stmt.close();
        } catch (SQLException e) {
            throw new ConnException(err);
        }
    }

    /**
     * Get method.
     * @return Returns {@link #me}.
     */
    public Person getMe(){
        return me;
    }

    /**
     * Get method.
     * @return Returns {@link #userType}.
     */
    public UserType getUserType(){
        return userType;
    }

    /**
     * Method for signing out of the database. Closing connection and setting
     * values of {@link #me} and {@link #userType} to null.
     */
    public void signOut(){
        me=null;
        userType=null;
        try {
            conn.close();
        }
        catch(SQLException e){
            conn=null;
        }
    }

    /**
     * Updates indicated person's password. If data is wrong, throws some exceptions.
     *
     * @param person Person, whose password is going to change.
     * @param newPassword String indicating new password.
     * @throws SQLException if something goes wrong in connection with database.
     * @throws ConnException if something goes wrong with data given by user.
     */
    public void changePass(Person person, String newPassword) throws SQLException, ConnException{
        if(isHacker(newPassword)){
            throw new ConnException(hacker);
        }
        Statement stat;
        stat = conn.createStatement();
        String table;
        if(person instanceof Student) {
            table = "Students";
        }
        else{
            table = "Teachers";
        }
        stat.executeUpdate("UPDATE "+table+" SET pass='"+newPassword+"' WHERE id = "+person.getId()+";");
        stat.close();
    }

    /**
     * This static method checks if parameter contains forbidden for SQL queries characters which may hack the database,
     * like ' " or ;
     * @param value checked String value
     * @return Returns true if value is 'hacking'
     */
    public static boolean isHacker(String value){
        if(value.contains("'") || value.contains("\"") || value.contains(";")){
            return true;
        }
        return false;
    }

    /**
     * This private method updates given by parameters values in the tables - Students or Teachers.
     *
     * @param person Person, whose data are to be changed.
     * @param value New value, to which data is to be set.
     * @param field SQL name of field, that is going to be changed.
     * @throws SQLException if something goes wrong in connection with database.
     * @throws ConnException if something goes wrong with data given by user.
     */
    private void update(Person person, String value, String field) throws SQLException, ConnException{
        if(isHacker(value) || isHacker(field)){
            throw new ConnException(hacker);
        }
        Statement stat;
        stat = conn.createStatement();
        String table;
        if(person instanceof Student) {
            table = "Students";
        }
        else{
            table = "Teachers";
        }
        stat.executeUpdate("UPDATE "+table+" SET "+field+"='"+value+"' WHERE id = "+person.getId()+";");
        if(field.equals("mail")){
            stat.executeUpdate("UPDATE Waiting SET mail='"+value+"' WHERE mail = '"+person.getMail()+"';");
        }
        stat.close();
    }

    /**
     * Changes person's mail, using method {@link #update(Person, String, String)}, after checking if new mail
     * for sure is not in the database.
     * @param person Person, whose mail is going to be changed.
     * @param mail New mail.
     * @throws SQLException if something goes wrong in connection with database.
     * @throws ConnException if something goes wrong with data given by user.
     */
    public void changeMail(Person person, String mail)throws SQLException,ConnException{
        if(isMailInDatabase(mail)){
            throw new ConnException(existing);
        }
        update(person, mail, "mail");

        person.setMail(mail);
    }

    /**
     * Changes student's student id, using method {@link #update(Person, String, String)} and setting new student id
     * to {@link Student}.
     * @param student Student, whose student id is going to be changed
     * @param student_id new value of student id.
     * @throws SQLException if something goes wrong in connection with database.
     * @throws ConnException if something goes wrong with data given by user.
     */
    public void changeStudentID(Student student, int student_id)throws SQLException,ConnException{
        update(student, String.valueOf(student_id), "student_id");
        student.setStudentID(student_id);
    }

    /**
     * Changes name of person. It is used only by admin, because
     * students and teachers can only ask for change of their names.
     * @param person Person, whose name is going to be changed.
     * @param name New value of name.
     * @throws SQLException if something goes wrong in connection with database.
     * @throws ConnException if something goes wrong with data given by user.
     */
    public void changeName(Person person, String name)throws SQLException,ConnException{
        update(person, name, "name");
        person.setName(name);
    }

    /**
     * Changes general group of student in SQL database.
     * @param student Students, whose genGroup is going to be changed.
     * @param genGroup new value of genGroup.
     * @throws SQLException if something goes wrong in connection with database.
     * @throws ConnException if something goes wrong with data given by user.
     */
    public void changeGenGroup(Student student, String genGroup)throws SQLException,ConnException{
        update(student, genGroup, "gen_class");
        student.setGenGroup(genGroup);
    }

    /**
     * Inserts query with new value into Waiting SQL table, asking admin for check and update. Person is always {@link #me}.
     * @param name New value.
     * @param type Type of value, corresponding with table column name.
     * @throws SQLException if something goes wrong in connection with database.
     * @throws ConnException if something goes wrong with data given by user.
     */
    public void askForChange(String name, String type)throws SQLException,ConnException{
        if(isHacker(name) || isHacker(type)){
            throw new ConnException(hacker);
        }
        Statement stat;
        stat = conn.createStatement();
        String table;
        if(isWaitingInDatabase(type)){
            stat.executeUpdate("UPDATE Waiting SET pass='"+name+"' WHERE mail='" +me.getMail() +"' AND type='"+type+"';");
        }
        else {
            stat.executeUpdate("INSERT INTO Waiting (mail, pass, type) VALUES ( '" +me.getMail() + "','" + name + "','" + type + "');");
        }
        stat.close();
    }

    /**
     * Gets group id, while given its name.
     * @param groupName Name of {@link Group}.
     * @return This group id.
     * @throws SQLException if something goes wrong in connection with database.
     * @throws ConnException if something goes wrong with data given by user.
     */
    public int getGroupIdByName(String groupName) throws SQLException, ConnException{
        if(isHacker(groupName)){
            throw new ConnException(hacker);
        }
        Statement stat = conn.createStatement();
        String query = "SELECT id FROM Classes WHERE name='"+groupName+"';";
        ResultSet result = stat.executeQuery(query);
        int val;
        if(result.next()) {
            val = result.getInt("id");
        }
        else throw new ConnException(notExitsting);
        stat.close();
        return val;
    }

    /**
     * Creates new group with given data. It is assumed that checking for duplicates was done before.
     * @param group necessary data for setting up new group in database, kept in object of class {@link Group}.
     * @throws SQLException if something goes wrong in connection with database.
     * @throws ConnException if something goes wrong with data given by user.
     */
    public void createGroup(Group group)throws SQLException, ConnException{
        Statement stat = conn.createStatement();
        String query;
        if(isHacker(group.getName())){
            throw new ConnException(hacker);
        }
        query="INSERT INTO Classes (name, day, start_hour, finish_hour) VALUES ('"+group.getName()+"', "+
                (group.getDayId()+1)+", '"+group.getStartHour()+"', '"+group.getFinishHour()+"');";
        stat.executeUpdate(query);

        query = "SELECT id FROM Classes WHERE name='"+group.getName()+"';";
        ResultSet result = stat.executeQuery(query);
        result.next();
        group.setId(result.getInt("id"));
        stat.close();
    }

    /**
     * Adds person to a group.
     * @param person {@link Person} added to group.
     * @param groupId Id of group, to which person is going to be added.
     * @throws SQLException if something goes wrong in connection with database.
     */
    public void addGroup(Person person, int groupId) throws SQLException{
        String table,query;
        if(person instanceof Student){
            table = "Studentsclasses (student, class) ";
            query = "student, class FROM Studentsclasses WHERE student=";
        }
        else {
            table = "Teachersclasses (teacher, class) ";
            query = "teacher, class FROM Teachersclasses WHERE teacher=";
        }
        Statement stat = conn.createStatement();

        ResultSet result = stat.executeQuery("SELECT "+query+person.getId()+" AND class="+groupId+";");
        if(!result.next()) {//there is no this class in database for this person
            stat.executeUpdate("INSERT INTO " + table + " VALUES (" + person.getId() + ", " + groupId + ");");
        }
        stat.close();
    }

    /**
     * Integer used in showing parts of sets of people or groups. It indicates last id of person or group that was shown.
     */
    private int lastId;

    /**
     * Used in {@link modules.attendancetaking.AttendanceTakingController}, method gets students from given group from
     * database.
     * @param showingState increased one by one int, indicating which part of students set is shown (there can be
     *                     max 27 students at once).
     * @param group {@link Group} of origin of all students taken by this method.
     * @return ArrayList of {@link Student}s, max of size 27.
     * @throws SQLException if something goes wrong in connection with database.
     */
    public ArrayList<Student> getStudents(int showingState, Group group) throws SQLException{
        if(isHacker(group.getName())){
            throw new SQLException();
        }
        if(showingState==0){
            lastId=0;
        }
        Statement stat = conn.createStatement();
        String query = "SELECT Students.id, Students.name FROM Students JOIN Studentsclasses" +
                " ON Students.id=Studentsclasses.student WHERE class="+group.getId()+" AND Students.id >= "+lastId+
                " ORDER BY Students.id LIMIT 27;";
        ResultSet result = stat.executeQuery(query);
        ArrayList<Student> students = new ArrayList<>();
        for(int i=0;i<27;i++){
            try {
                Student student = new Student(result, false);
                students.add(student);
            }
            catch(SQLException e){
                break;
            }
        }
        lastId=(students.size()==0)?0:(students.get(students.size()-1).getId()+1);
        stat.close();
        return students;
    }

    /**
     * Inserts given data into attendance.
     * @param students set of students with information about their attendance.
     * @param group Group of origin of these students.
     * @throws SQLException if something goes wrong in connection with database.
     */
    public void takeAttendance(ArrayList<Student> students, Group group) throws SQLException{
        Statement stat = conn.createStatement();
        String query = "INSERT INTO Attendance (student, class, date, present) values ";
        for(Student student: students){
            query += "("+student.getId()+", "+group.getId()+", '"+
                    student.getAttendance().getDate()+"', "+student.getAttendance().isPresent()+"), ";
        }
        query = query.substring(0, query.length()-2)+";";
        stat.executeUpdate(query);
        stat.close();
    }

    /**
     * This method gets max 27 groups from SQL database.
     * @param showingState increased one by one int, indicating which part of groups set is shown (there can be
     *                     max 27 groups at once).
     * @return ArrayList of Groups, max of size 27.
     * @throws SQLException if something goes wrong in connection with database.
     */
    public ArrayList<Group> getGroups(int showingState)throws SQLException{
        if(showingState==0){
            lastId=0;
        }
        Statement stat = conn.createStatement();
        String query;
        if(userType==UserType.admin) {
            query = "SELECT * FROM Classes WHERE id >= " + lastId + " ORDER BY id;";
        }
        else if(userType == UserType.teacher){
            query = "SELECT * FROM Classes INNER JOIN Teachersclasses" +
                    " on Teachersclasses.class=Classes.id WHERE Teachersclasses.teacher="+me.getId()+
                    " AND Classes.id >= " + lastId + " ORDER BY Classes.id;";
        }
        else{ //if(userType == UserType.student){
            query = "SELECT * FROM Classes INNER JOIN Studentsclasses" +
                    " ON Studentsclasses.class=Classes.id WHERE Studentsclasses.student="+me.getId()+
                    " AND Classes.id >= " + lastId + " ORDER BY Classes.id;";
        }
        ResultSet result = stat.executeQuery(query);
        ArrayList<Group> groups = new ArrayList<Group>();
        for(int i=0;i<27;i++){
            try {
                Group group = new Group(result, BuildingType.normal);
                groups.add(group);
            }
            catch(SQLException e){
                break;
            }
        }
        stat.close();
        return groups;
    }

    /**
     * Used in {@link modules.attendance.AttendanceController}, gets information about student's attendance.
     * @param group Group of origin of students.
     * @return ArrayList of Students with information about their attendance. There can be duplicates of students,
     * because each attendance set gets their student.
     * @throws SQLException if something goes wrong in connection with database.
     */
    public ArrayList<Student> getAttendance(Group group) throws SQLException{
        Statement stat = conn.createStatement();
        String query = "SELECT Attendance.id, Students.id, Students.name, date, present FROM Attendance " +
                "INNER JOIN Students ON Attendance.student=Students.id WHERE ";
        if(userType==UserType.student){
            query += "Students.id="+me.getId()+" AND ";
        }
        query+="Attendance.class="+group.getId()+" ORDER BY date DESC, Students.name;";

        ResultSet result = stat.executeQuery(query);
        ArrayList<Student> students = new ArrayList<Student>();
        while(true){
            try {
                Student student = new Student(result, true);
                students.add(student);
            }
            catch(SQLException e){
                break;
            }
        }
        stat.close();
        return students;
    }

    /**
     * Updates information about attendance in given group.
     * @param students updated set of students with information about their attendance.
     * @param group group of origin of all students in parameter before.
     * @throws SQLException
     */
    public void updateAttendance(ArrayList<Student> students, Group group) throws SQLException{
        Statement stat = conn.createStatement();
        String query = "";
        for(Student student: students){
            query = "UPDATE Attendance SET present = "+student.getAttendance().isPresent()+", date='"+
                    student.getAttendance().getDate()+"' WHERE id="+student.getAttendance().getId()+";\n";
            stat.executeUpdate(query);
        }
        stat.close();
    }

    /**
     * Gets students or teachers connected with this student or teacher. For admin, it gets all students or all teachers.
     * @param onlyStudents boolean indicating (for admin), if they want students (true) or teachers (false). The rest
     *                     of users can get only students or only teachers.
     * @return ArrayList of people being students or teachers.
     * @throws SQLException if something goes wrong in connection with database.
     */
    public ArrayList<Person> getPeople(boolean onlyStudents) throws SQLException{
        ArrayList<Person> people = new ArrayList<>();
        Statement stat = conn.createStatement();
        String query;
        if(userType == UserType.student){
            query = "SELECT * FROM Teachers LEFT JOIN Teachersclasses ON Teachers.id=Teachersclasses.teacher " +
                    "LEFT JOIN Classes ON Teachersclasses.class=Classes.id WHERE Classes.id IN " +
                    "(SELECT id FROM Studentsclasses WHERE student="+me.getId()+");";
            ResultSet result = stat.executeQuery(query);
            while(result.next()) {
                people.add(new Teacher(result, BuildingType.full));
            }
        }
        else if(userType == UserType.teacher){
            query = "SELECT * FROM Students LEFT JOIN Studentsclasses ON Students.id=Studentsclasses.student " +
                    "LEFT JOIN Classes ON Studentsclasses.class=Classes.id WHERE Classes.id IN " +
                    "(SELECT id FROM Teachersclasses WHERE teacher="+me.getId()+");";
            ResultSet result = stat.executeQuery(query);
            while(result.next()) {
                people.add(new Student(result, BuildingType.full));
            }
        }
        else {//admin
            if(onlyStudents) {
                query = "SELECT * FROM Students;";
                ResultSet result = stat.executeQuery(query);
                while (result.next()) {
                    people.add(new Student(result, BuildingType.fullAdmin));
                }
            }
            else {
                query = "SELECT * FROM Teachers;";
                ResultSet result = stat.executeQuery(query);
                while (result.next()) {
                    people.add(new Teacher(result, BuildingType.fullAdmin));
                }
            }
        }
        return people;
    }

    /**
     * Adds new person to database.
     * @param person information about this person kept in class {@link Person}.
     * @throws SQLException if something goes wrong in connection with database.
     */
    public void addPerson(Person person) throws SQLException{
        if(isMailInDatabase(person.getMail())){
            throw new SQLException();
        }
        Statement stat = conn.createStatement();
        String query;
        if(person instanceof Teacher){
            query="INSERT INTO Teachers (mail, pass, name) VALUES ('"+person.getMail()+"', '"+
                    person.getPass()+"', '"+person.getName()+"');";
        }
        else{//student
            query = "INSERT INTO Students (mail, pass, name, student_id, gen_class) VALUES ('"+person.getMail()+"', '"+
                    person.getPass()+"', '"+person.getName()+"', "+((Student)person).getStudentID()+", '"+
                    ((Student)person).getGenGroup()+"');";
        }
        stat.executeUpdate(query);
    }

    /**
     * Gets groups of this student or this teacher.
     * @return ordered by time ArrayList of Groups
     * @throws SQLException if something goes wrong in connection with database.
     */
    public ArrayList<Group> getTimetable() throws SQLException{
        Statement stat = conn.createStatement();
        String query;
        if(userType == UserType.teacher || userType==UserType.admin){
            query = "SELECT * FROM Classes INNER JOIN Teachersclasses" +
                    " ON Teachersclasses.class=Classes.id WHERE Teachersclasses.teacher="+me.getId()+
                    " ORDER BY Classes.day, Classes.start_hour;";
        }
        else{ //if(userType == UserType.student){
            query = "SELECT * FROM Classes INNER JOIN Studentsclasses" +
                    " ON Studentsclasses.class=Classes.id WHERE Studentsclasses.student="+me.getId()+
                    " ORDER BY Classes.day, Classes.start_hour;";
        }
        ResultSet result = stat.executeQuery(query);
        ArrayList<Group> groups = new ArrayList<Group>();
        while(result.next()) {
            Group group = new Group(result, BuildingType.full);
            groups.add(group);
        }
        stat.close();
        return groups;
    }

}
