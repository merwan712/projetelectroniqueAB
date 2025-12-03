#include "schematicwidget.h"
#include <QPainter>
#include <QPainterPath>

SchematicWidget::SchematicWidget(QWidget *parent)
    : QWidget(parent)
{
    // Rôle : Constructeur de base. Établit la hiérarchie des widgets (ce widget est l'enfant de 'parent').

    // Initialisation technique : Prépare le fond du widget pour que notre QPainter puisse dessiner dessus
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

void SchematicWidget::setEquation(QString equation)
{
    // coupe le texte à l'endroit du  =.
    if (equation.contains("=")) {
        m_equation = equation.split("=").last().trimmed();
    } else {
        // Si pas de =  on prend tout le texte
        m_equation = equation;
    }
    update();
}

void SchematicWidget::setInputValues(QMap<QString, int> values)
{
    m_currentValues = values;//maj avec nouvelle val
    update();
}



void SchematicWidget::drawLogicLabel(QPainter &painter, int x, int y, int value)// dessine la valeur sur le fil
{
    painter.save();

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 10, QFont::Bold));

    // Zone de texte située juste au-dessus du fil
    QRect rect(x - 10, y - 18, 20, 15);

    painter.drawText(rect, Qt::AlignCenter, QString::number(value));

    painter.restore();
}

// --- DESSIN DES PORTES (Formes IEEE) ---
void drawIEEEGate(QPainter &painter, QString type, int x, int y)
{
    QRect rect(x, y - 20, 50, 40);
    QColor fillColor(60, 70, 80);
    painter.setBrush(fillColor);
    painter.setPen(QPen(Qt::white, 2));

    QPainterPath path;

    if (type == "AND") {
        path.moveTo(x, y - 20);
        path.lineTo(x + 25, y - 20);
        path.arcTo(x, y - 20, 50, 40, 90, -180);
        path.lineTo(x, y + 20);
        path.lineTo(x, y - 20);
        painter.drawPath(path);
    }
    else if (type == "OR") {
        path.moveTo(x, y - 20);
        path.quadTo(x + 35, y - 20, x + 50, y);
        path.quadTo(x + 35, y + 20, x, y + 20);
        path.quadTo(x + 15, y, x, y - 20);
        painter.drawPath(path);
    }
    else if (type == "XOR") {
        int offset = 5;
        QPainterPath body;
        body.moveTo(x + offset, y - 20);
        body.quadTo(x + 35 + offset, y - 20, x + 50, y);
        body.quadTo(x + 35 + offset, y + 20, x + offset, y + 20);
        body.quadTo(x + 15 + offset, y, x + offset, y - 20);
        painter.drawPath(body);

        QPainterPath backBar;
        backBar.moveTo(x - 5, y - 20);
        backBar.quadTo(x + 10, y, x - 5, y + 20);
        painter.setBrush(Qt::NoBrush);
        painter.drawPath(backBar);
    }
    else if (type == "NOT") {
        QPolygon polygon;
        polygon << QPoint(x, y - 15) << QPoint(x, y + 15) << QPoint(x + 35, y);
        painter.drawPolygon(polygon);
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(x + 35, y - 5, 10, 10);
    }
}

// --- DESSIN RÉCURSIF (Arbre) ---
QPair<QPoint, int> SchematicWidget::drawRecursive(QPainter &painter, QString expr, int x, int y, int heightStep)
{
    expr = expr.trimmed();
    QString op;
    int splitIndex = findMainOperator(expr, op);

    // Enlever parenthèses extérieures
    if (splitIndex == -1 && !expr.startsWith("not ", Qt::CaseInsensitive)) {
        if (expr.startsWith("(") && expr.endsWith(")")) {
            return drawRecursive(painter, expr.mid(1, expr.length()-2), x, y, heightStep);
        }
    }

    // --- CAS NOT ---
    if (splitIndex == -1 && expr.startsWith("not ", Qt::CaseInsensitive)) {
        drawIEEEGate(painter, "NOT", x, y);
        QString subExpr = expr.mid(4).trimmed();

        QPair<QPoint, int> child = drawRecursive(painter, subExpr, x - 80, y, heightStep);

        painter.setPen(QPen(Qt::white, 2));
        painter.drawLine(child.first.x(), child.first.y(), x, y);

        int myValue = !child.second;
        // Chiffre posé après la bulle
        drawLogicLabel(painter, x + 50, y, myValue);
        return {QPoint(x + 45, y), myValue};
    }

    // --- CAS VARIABLE (X, Y...) ---
    if (splitIndex == -1) {
        painter.setPen(Qt::white);

        // Police taille 14
        painter.setFont(QFont("Segoe UI", 14, QFont::Bold));

        // Texte décalé pour ne pas toucher le chiffre
        QRect textRect(x - 65, y - 20, 50, 40);
        painter.drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, expr);

        QString varName = expr.toUpper();
        int val = m_currentValues.value(varName, 0);

        // Chiffre posé sur le fil (décalé vers la droite)
        drawLogicLabel(painter, x + 15, y, val);

        return {QPoint(x, y), val};
    }

    // --- CAS BINAIRE (AND, OR, XOR) ---
    drawIEEEGate(painter, op, x, y);

    int opLength = (op == "OR") ? 4 : 5;
    if (op == "XOR") opLength = 5;
    QString leftExpr = expr.left(splitIndex).trimmed();
    QString rightExpr = expr.mid(splitIndex + opLength).trimmed();

    int leavesTop = countLeaves(leftExpr);
    int leavesBottom = countLeaves(rightExpr);
    int unit = 40;

    int yOffsetTop = (leavesBottom * unit / 2) + 10;
    int yOffsetBottom = (leavesTop * unit / 2) + 10;
    if (yOffsetTop < 30) yOffsetTop = 30;
    if (yOffsetBottom < 30) yOffsetBottom = 30;

    int nextX = x - 80;
    int connectOffset = (op == "OR" || op == "XOR") ? 5 : 0;

    QPair<QPoint, int> p1 = drawRecursive(painter, leftExpr, nextX, y - yOffsetTop, heightStep);
    QPair<QPoint, int> p2 = drawRecursive(painter, rightExpr, nextX, y + yOffsetBottom, heightStep);

    auto drawWire = [&](QPoint start, QPoint end) {
        int midX = (start.x() + end.x()) / 2;
        painter.drawLine(start.x(), start.y(), midX, start.y());
        painter.drawLine(midX, start.y(), midX, end.y());
        painter.drawLine(midX, end.y(), end.x(), end.y());
    };

    painter.setPen(QPen(Qt::white, 2));
    drawWire(p1.first, QPoint(x + connectOffset, y - 10));
    drawWire(p2.first, QPoint(x + connectOffset, y + 10));

    int myValue = 0;
    if (op == "AND") myValue = p1.second && p2.second;
    if (op == "OR")  myValue = p1.second || p2.second;
    if (op == "XOR") myValue = p1.second ^ p2.second;

    // Chiffre posé à la sortie de la porte
    drawLogicLabel(painter, x + 55, y, myValue);

    return {QPoint(x + 50, y), myValue};
}

int SchematicWidget::countLeaves(QString expr)//compter le nb d'entree pour calculer la taille nescessaire
{
    expr = expr.trimmed();
    QString op;
    int splitIndex = findMainOperator(expr, op);

    if (splitIndex == -1 && !expr.startsWith("not ", Qt::CaseInsensitive)) {
        return 1;
    }
    if (splitIndex == -1 && expr.startsWith("not ", Qt::CaseInsensitive)) {
        return countLeaves(expr.mid(4));
    }

    int opLength = (op == "OR") ? 4 : 5;
    if (op == "XOR") opLength = 5;

    QString leftExpr = expr.left(splitIndex);
    QString rightExpr = expr.mid(splitIndex + opLength);

    return countLeaves(leftExpr) + countLeaves(rightExpr);
}

void SchematicWidget::paintEvent(QPaintEvent *event)//desine la partie final vers le S
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Fond sombre
    painter.fillRect(rect(), QColor(45, 45, 48));

    if (m_equation.isEmpty()) return;

    int startX = width() - 100;
    int startY = height() / 2;

    QPair<QPoint, int> result = drawRecursive(painter, m_equation, startX, startY, 80);
    QPoint endPoint = result.first;

    // Fil final vers S
    painter.setPen(QPen(Qt::white, 2));
    painter.drawLine(endPoint.x(), endPoint.y(), width() - 50, startY);

    // Texte S (Grand)
    painter.setFont(QFont("Segoe UI", 14, QFont::Bold));
    painter.drawText(width() - 40, startY + 5, "S");
}

int SchematicWidget::findMainOperator(const QString &expr, QString &opType)
{
    int level = 0;
    for (int i = expr.length() - 1; i >= 0; i--)// On scanne l'expression
    {
        QChar c = expr[i];
        if (c == ')') level++; else if (c == '(') level--;
        if (level == 0) {
            if (expr.mid(i, 4).toLower() == " or ") { opType = "OR"; return i; }
            if (expr.mid(i, 5).toLower() == " xor ") { opType = "XOR"; return i; }
        }
    }
    level = 0;
    for (int i = expr.length() - 1; i >= 0; i--) {
        QChar c = expr[i];
        if (c == ')') level++; else if (c == '(') level--;
        if (level == 0) {
            if (expr.mid(i, 5).toLower() == " and ") { opType = "AND"; return i; }
        }
    }
    return -1;
}
