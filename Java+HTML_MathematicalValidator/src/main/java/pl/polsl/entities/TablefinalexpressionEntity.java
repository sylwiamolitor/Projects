package pl.polsl.entities;

import javax.persistence.*;

@Entity
@Table(name = "TABLEFINALEXPRESSION", schema = "APP")
public class TablefinalexpressionEntity {
    private int id;
    private String expressionwithtags;
    private String expressionaftercorrection;

    @Id
    @Column(name = "ID")
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    @Basic
    @Column(name = "EXPRESSIONWITHTAGS")
    public String getExpressionwithtags() {
        return expressionwithtags;
    }

    public void setExpressionwithtags(String expressionwithtags) {
        this.expressionwithtags = expressionwithtags;
    }

    @Basic
    @Column(name = "EXPRESSIONAFTERCORRECTION")
    public String getExpressionaftercorrection() {
        return expressionaftercorrection;
    }

    public void setExpressionaftercorrection(String expressionaftercorrection) {
        this.expressionaftercorrection = expressionaftercorrection;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        TablefinalexpressionEntity that = (TablefinalexpressionEntity) o;

        if (id != that.id) return false;
        if (expressionwithtags != null ? !expressionwithtags.equals(that.expressionwithtags) : that.expressionwithtags != null)
            return false;
        if (expressionaftercorrection != null ? !expressionaftercorrection.equals(that.expressionaftercorrection) : that.expressionaftercorrection != null)
            return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = id;
        result = 31 * result + (expressionwithtags != null ? expressionwithtags.hashCode() : 0);
        result = 31 * result + (expressionaftercorrection != null ? expressionaftercorrection.hashCode() : 0);
        return result;
    }
}
