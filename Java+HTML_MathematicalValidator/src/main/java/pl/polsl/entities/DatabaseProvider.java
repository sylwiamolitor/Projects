package pl.polsl.entities;



import java.sql.*;

/**
 * Class that contains provider of the database
 *   @since 5.0
 *   @author Sylwia Molitor
 *   @version 1.0
 */
public class DatabaseProvider {

    /**
     * Instance of the DatabaseProvider
     */
    private static DatabaseProvider instance;
    /**
     * Connection
     */
    private static Connection connection;

    /**
     * Init for DatabaseProvider
     * @throws SQLException exception
     */
    private void init() throws SQLException
    {

        try {
            connection = DriverManager.getConnection("jdbc:derby://localhost:1527/database", "app", "app");
        }
        catch(SQLException message)
        {
            message.getMessage();
        }
        connection.setAutoCommit(false);
        Statement statement = null;
        try {
            statement = connection.createStatement();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }

        statement = connection.createStatement();

    }

    /**
     * Constructor
     * @throws ClassNotFoundException exception
     * @throws SQLException exception
     */
    private DatabaseProvider() throws ClassNotFoundException, SQLException
    {

        try {
            Class.forName("org.apache.derby.jdbc.ClientDriver");
        }
        catch(ClassNotFoundException message)
        {
            message.getMessage();
        }
        init();
    }

    /**
     * For executing Query
     * @param sqlQuery Query to execute
     * @return ResultSet
     * @throws ClassNotFoundException exception
     * @throws SQLException exception
     */
    public static ResultSet query(String sqlQuery) throws ClassNotFoundException, SQLException
    {
        if (instance == null)
        {
            instance = new DatabaseProvider();
        }
        if (instance.connection.isClosed())
        {
            instance.init();
        }
        Statement statement = null;
        try {
            statement = connection.createStatement();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }

        ResultSet rs= statement.executeQuery(sqlQuery);
        connection.commit();
        return rs;
    }

    /**
     * For executing Query (different kind)
     * @param sqlQuery Query to execute
     * @return 1
     * @throws ClassNotFoundException exception
     * @throws SQLException exception
     */
    public static int query2(String sqlQuery) throws ClassNotFoundException, SQLException
    {

        if (instance == null)
        {
            instance = new DatabaseProvider();
        }
        if (instance.connection.isClosed())
        {
            instance.init();
        }
        Statement statement = null;
        try {
            statement = connection.createStatement();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
        if (instance != null) {
            statement.executeUpdate(sqlQuery);
        }
        connection.commit();
        return 1;

    }

}