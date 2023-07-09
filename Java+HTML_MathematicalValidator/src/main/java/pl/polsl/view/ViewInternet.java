package pl.polsl.view;

import pl.polsl.controller.Table;
import pl.polsl.entities.FinalExpression;
import pl.polsl.entities.InputExpression;

import javax.servlet.http.Cookie;
import java.io.PrintWriter;
import java.util.List;

/**
 * Class for viewing in HTML application.
 * pl.polsl.view.ViewInternet
 *   @since 6.0
 *   @author Sylwia Molitor
 *   @version 1.0
 */
public class ViewInternet {

    /**
     * Prints the beginning of HTML site.
     * @param out PrintWriter
     */
    public void printBeginningOfHTML(PrintWriter out) {

        out.println("<HTML><HEAD><TITLE>Checked!:");
        out.println("</TITLE></HEAD><BODY>");
    }

    /**
     * Prints the end of HTML site.
     * @param out PrintWriter
     */
    public void printEndOfHTML(PrintWriter out)
    {
        out.println("<FORM ACTION=\"/SprawdzPoprawnoscWyrazeniaMatematycznegoInternet_war_exploded/index.jsp\" method=\"GET\" >\n" +
            "    Go back?\n" +
            "    <input type=\"submit\" name=\"button2\" value=\"YES\">\n" +
            "</FORM>");

    }

    /**
     * Prints cookies with expressions - their number, name and values.
     * @param out PrintWriter
     * @param ck cookie table
     */
    public void printAllCookies(PrintWriter out, Cookie[] ck)
    {
        out.println("All entered expressions: <br> Cookie has expression before correction in name and expression after correction in value <br>");
        for(int i=1;i<ck.length;i++)
            out.print("<br> Cookie number " + i +": "+ck[i].getName()+" | "+ck[i].getValue());//printing name and value of cookie

    }

    /**
     * Prints all expressions before, during and after correction in current session.
     * @param out PrintWriter
     * @param allExpressions list of Tables with expressions before, during and after correction.
     */
    public void printAllExpressions(PrintWriter out, List<Table> allExpressions)
    {
        for(Table table: allExpressions) {
            out.println("Expression before correction: " + table.getExpressionBefore());
            out.println("Expression with tags: " + table.getExpressionDuring());
            out.println("Expression after correction: " + table.getExpressionAfter());
            out.println("<br> <br>");
        }
    }

    /**
     * Shows information about exceptions if there are any.
     * @param out PrintWriter
     * @param type type of exception - true if division by zero, false if not allowed sign
     */
    public void showExceptionInformation(PrintWriter out, boolean type) {
        if (type)
            out.println("There was division by zero exception!<br>");
        else
            out.println("There was not allowed sign exception!<br>");
    }

    /**
     * Prints current expression before, during and after correction.
     * @param out PrintWriter
     * @param expression current  expression before, during and after correction.
     */
    public void printExpression(PrintWriter out, Table expression)
    {
        out.println("Your expression: " + expression.getExpressionBefore() + "<br>");
        out.println(" Your expression after checking: " + expression.getExpressionDuring() + "<br>");
        out.println(" Your expression after correction: " + expression.getExpressionAfter() + "<br>");

    }
    /**
     * Shows advice if there are any errors.
     * @param out PrintWriter
     * @param typeOfErrors 2 if brackets' errors, 1 if signs' errors
     */
    public void showAdvice(PrintWriter out, int typeOfErrors) {

            if (typeOfErrors == 2) {
               out.println("Wrong number of brackets!");
            }
            if (typeOfErrors == 1) {
                out.println("You should delete some symbols (after '$' sign) or check if the brackets are ')(' instead of '()'");
            }
    }
    /**
     * Shows number of errors and their type if there are any errors.
     * @param out PrintWriter
     * @param signsErrors  number of signs' errors
     * @param bracketsErrors number of brackets' errors
     *
     */
    public void showNumberOfErrors(PrintWriter out, int signsErrors, int bracketsErrors)
    {

        out.println("<br>Number of brackets' errors: " + bracketsErrors);
        out.println("<br>Number of signs' errors: "+ signsErrors + "<br>");
    }

    /**
     * Prints information about correct expression or the lack of input expression.
     * @param out PrintWriter
     * @param test true if correct expression, false if no input expression
     */
    public void printCorrectOrTheLackOfTheExpression(PrintWriter out, boolean test)
    {

        if(test)
            out.println("It was correct! <br>");
        else
            out.println("There wasn't any expression! <br> ");
    }

    /**
     * Prints database
     * @param out PrintWriter
     * @param inputToPrint input expressions
     * @param finalToPrint output expressions
     */
    public void printDatabase(PrintWriter out, List<InputExpression> inputToPrint, List<FinalExpression> finalToPrint)
    {
        out.println("FROM DATABASE FOR EXERCISE 5: <br>ALL INPUT EXPRESSIONS:<br>");
        for(InputExpression x : inputToPrint) {
            out.println("<br>ID: " + x.getId() + " input: " + x.getInputExpression() + "<br>");

        }
        out.println("FROM DATABASE FOR EXERCISE 5: <br>ALL OUTPUT EXPRESSIONS:<br>");

        for(FinalExpression x : finalToPrint)
            out.println("<br>ID: "+x.getId() + " with tags: "+ x.getExpressionWithTags()+" after correction: "+ x.getExpressionAfterCorrection()+"<br>");


    }

}
