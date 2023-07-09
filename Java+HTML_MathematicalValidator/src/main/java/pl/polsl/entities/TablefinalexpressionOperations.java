package pl.polsl.entities;



import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
 * Class that contains operations on table with ID, expression with tags and final expression
 *   @since 5.0
 *   @author Sylwia Molitor
 *   @version 1.0
 */
public class TablefinalexpressionOperations {

    /**
     * Constructor that contains create table.
     */
    public TablefinalexpressionOperations()
    {

        try {
            DatabaseProvider.query2("CREATE TABLE TABLEFINALEXPRESSION (id INTEGER, expressionWithTags VARCHAR(100), expressionAfterCorrection VARCHAR(100), PRIMARY KEY (id), FOREIGN KEY (id) REFERENCES TABLEINPUTEXPRESSION(id))");

        } catch (SQLException throwables) {
            throwables.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

    }

    /**
     * Returns all expressions in the table - SELECT *
     * @return all expressions in the table
     */
    public List<FinalExpression> getAllExpressions()
    {

        List<FinalExpression> list = new ArrayList<>();

        try {
            ResultSet rs = DatabaseProvider.query("SELECT * FROM TABLEFINALEXPRESSION");

            while (rs.next()) {
                    list.add(new FinalExpression(rs.getInt("ID"), rs.getString("EXPRESSIONWITHTAGS"),rs.getString("EXPRESSIONAFTERCORRECTION")));
            }


        } catch (SQLException | ClassNotFoundException throwables) {
            throwables.printStackTrace();
        }

        return list;
    }

    /**
     * Adds expressions to the database.
     * @param id id of added expression
     * @param expressionWithTags   expression with tags
     * @param expressionAfterCorrection   final expression
     * @throws SQLException exception
     * @throws ClassNotFoundException   exception
     */
    public void addExpression(int id, String expressionWithTags, String expressionAfterCorrection) throws SQLException, ClassNotFoundException {
        DatabaseProvider.query2("INSERT INTO TABLEFINALEXPRESSION(ID, EXPRESSIONWITHTAGS, EXPRESSIONAFTERCORRECTION) VALUES ("+id+", '"+expressionWithTags+"', '"+expressionAfterCorrection+"')");
    }

    /**
     * Deletes expression from database
     * @param id id of the deleted expression
     * @throws SQLException exception
     * @throws ClassNotFoundException   exception
     */
    public void deleteExpression(int id) throws SQLException, ClassNotFoundException {

        DatabaseProvider.query2("DELETE FROM TABLEFINALEXPRESSION WHERE ID = "+id);

    }
    /**
     * Updates expression from database
     * @param id id of the updated expression
     * @param expressionWithTags   new expressionWithTags for old expression
     * @param expressionAfterCorrection   new expressionAfterCorrection for old expression
     * @throws SQLException exception
     * @throws ClassNotFoundException   exception
     */
    public void updateExpression(int id, String expressionWithTags, String expressionAfterCorrection) throws SQLException, ClassNotFoundException {

        DatabaseProvider.query2("UPDATE TABLEFINALEXPRESSION SET ID = "+id+", EXPRESSIONWITHTAGS = '"+expressionWithTags+"', EXPRESSIONAFTERCORRECTION = '"+expressionAfterCorrection+"' WHERE ID = "+id);

    }

}
