package pl.polsl.entities;

import javax.persistence.*;

@Entity
@Table(name = "TABLEINPUTEXPRESSION", schema = "APP")
public class TableinputexpressionEntity {
    private int id;
    private String inputexpression;

    @Id
    @Column(name = "ID")
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    @Basic
    @Column(name = "INPUTEXPRESSION")
    public String getInputexpression() {
        return inputexpression;
    }

    public void setInputexpression(String inputexpression) {
        this.inputexpression = inputexpression;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        TableinputexpressionEntity that = (TableinputexpressionEntity) o;

        if (id != that.id) return false;
        if (inputexpression != null ? !inputexpression.equals(that.inputexpression) : that.inputexpression != null)
            return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = id;
        result = 31 * result + (inputexpression != null ? inputexpression.hashCode() : 0);
        return result;
    }
}
