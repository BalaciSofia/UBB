#include "chart.h"
#include <QPainter>
#include <QFontMetrics>
#include <algorithm>

chart::chart(std::map<QString, int> ageGroups, QWidget *parent)
    : QWidget(parent), breedCounts(ageGroups) // now used for age group counts
{
    setMinimumSize(400, 300);
}

void chart::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);

    int barWidth = 60;
    int spacing = 40;
    int margin = 50;

    int maxHeight = height() - 2 * margin;
    int maxCount = 0;
    for (const auto &pair : breedCounts)
        maxCount = std::max(maxCount, pair.second);

    int x = margin;
    for (const auto &pair : breedCounts) {
        int barHeight = static_cast<int>((static_cast<double>(pair.second) / maxCount) * maxHeight);
        QRect rect(x, height() - margin - barHeight, barWidth, barHeight);
        painter.fillRect(rect, Qt::green);
        painter.drawRect(rect);

        // Label below bar
        QString label = pair.first;
        QFontMetrics fm(painter.font());
        int textWidth = fm.horizontalAdvance(label);
        painter.drawText(x + (barWidth - textWidth) / 2, height() - margin + 20, label);

        // Value above bar
        painter.drawText(x + (barWidth / 2) - 10, height() - margin - barHeight - 5, QString::number(pair.second));

        x += barWidth + spacing;
    }
}
