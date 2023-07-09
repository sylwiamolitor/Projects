package pl.polsl.entities;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
 * Class that contains operations on table with ID and inputexpression
 *   @since 5.0
 *   @author Sylwia Molitor
 *   @version 1.0
 */
public class TableinputexpressionOperations {


    /**
     * Constructor that contains create table.
     */
    public TableinputexpressionOperations()
    {
        try {
            DatabaseProvider.query2("CREATE TABLE TABLEINPUTEXPRESSION (id INTEGER, inputExpression VARCHAR(100),PRIMARY KEY (id)) ");
        } catch (SQLException | ClassNotFoundException throwables) {
            throwables.printStackTrace();
        }

    }

    /**
     * Returns all expressions in the table - SELECT *
     * @return all expressions in the table
     */
    public List<InputExpression> getAllExpressions()
    {
        List<InputExpression> list = new ArrayList<>();

        try {


            ResultSet rs = DatabaseProvider.query("SELECT * FROM TABLEINPUTEXPRESSION");


            while (rs.next()) {
                list.add(new InputExpression(rs.getInt("ID"), rs.getString("INPUTEXPRESSION")));
            }


        } catch (SQLException | ClassNotFoundException throwables) {
            throwables.printStackTrace();
        }

        return list;
    }

    /**
     * Adds expression to the database.
     * @param id id of added expression
     * @param inputExpression   input expression
     * @throws SQLException exception
     * @throws ClassNotFoundException   exception
     */
    public void addExpression(int id, String inputExpression) throws SQLException, ClassNotFoundException {

        DatabaseProvider.query2("INSERT INTO TABLEINPUTEXPRESSION(ID, INPUTEXPRESSION) VALUES ("+id+", '"+inputExpression+"')");
    }


    /**
     * Deletes expression from database
     * @param id id of the deleted expression
     * @throws SQLException exception
     * @throws ClassNotFoundException   exception
     */
    public void deleteExpression(int id) throws SQLException, ClassNotFoundException {

        DatabaseProvider.query2("DELETE FROM TABLEINPUTEXPRESSION WHERE ID = "+id);

    }

    /**
     * Updates expression from database
     * @param id id of the updated expression
     * @param inputExpression   new inputExpression for old expression
     * @throws SQLException exception
     * @throws ClassNotFoundException   exception
     */
    public void updateExpression(int id, String inputExpression) throws SQLException, ClassNotFoundException {

        DatabaseProvider.query2("UPDATE  TABLEINPUTEXPRESSION SET ID = "+id+", INPUTEXPRESSION = '"+inputExpression+"' WHERE ID = "+id);

    }

}
