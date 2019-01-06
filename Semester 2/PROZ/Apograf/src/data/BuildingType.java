package data;

/**
 * Enum class, indicating types of constructing classes {@link Student}, {@link Group}, {@link Teacher}. It is used in
 * different {@link mains.Model} settings of constructing {@link data} objects.
 * @author Wojciech Sitek
 * @version 1.0
 * @since 2018-06-03
 */
public enum BuildingType{
    /**
     * Normal building indicates that constructor itself changes rows of {@link java.sql.ResultSet}.
     */
    normal,
    /**
     * Full building type indicates that constructor includes {@link Group} constructing and constructor doesn't change
     * rows of {@link java.sql.ResultSet}.
     */
    full,
    /**
     * FullAdmin building type indicates that constructor doesn't include {@link Group} constructing and doesn't change
     * rows of {@link java.sql.ResultSet}. These are settings for admin.
     */
    fullAdmin};
