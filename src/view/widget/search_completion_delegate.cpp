// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "search_completion_delegate.h"
#include "base/utils.h"
#include "base/ddlog.h"

#include <DStyleHelper>
#include <DPaletteHelper>
#include <QPainterPath>

SearchCompletionDelegate::SearchCompletionDelegate(QAbstractItemView *parent)
    : DStyledItemDelegate(parent)
    , m_parentView(parent)
{
    qCDebug(app) << "SearchCompletionDelegate constructor called";
}

//用于去除选中项的边框
void SearchCompletionDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    if (index.isValid()) {
        qCDebug(app) << "Painting completion item at row:" << index.row();
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing, true);

        QVariant varErrorItem = index.data(Qt::DisplayRole);
        //20210629 codereview
        if (!varErrorItem.isValid()) {
            qCWarning(app) << "Invalid item data at index:" << index;
            return;
        }

        SearchCompletionItemModel itemModel = varErrorItem.value<SearchCompletionItemModel>();

        QString strSearchKeyword = itemModel.strSearchKeyword;
        QString strSearchAppDisplayName = itemModel.strSearchAppDisplayName;
        qCDebug(app) << "Item data - keyword:" << strSearchKeyword
                    << "app:" << strSearchAppDisplayName;

        QStyleOptionViewItem viewOption(option); //用来在视图中画一个item

        DPalette::ColorGroup cg = (option.state & QStyle::State_Enabled) ? DPalette::Normal : DPalette::Disabled;
        if (cg == DPalette::Normal && !(option.state & QStyle::State_Active)) {
            cg = DPalette::Inactive;
        }

        QFont nameFont;
        nameFont.setPixelSize(DFontSizeManager::instance()->fontPixelSize(DFontSizeManager::T6));
        nameFont.setWeight(QFont::Medium);
        painter->setFont(nameFont);

        QString searchText = QString("%1(%2)").arg(strSearchKeyword, strSearchAppDisplayName);
        qCDebug(app) << "Formatted search text:" << searchText;

        if (option.state & QStyle::State_Selected) {
            qCDebug(app) << "Painting selected item";
            QPainterPath path;
            QRect rect;
            rect.setX(option.rect.x());
            rect.setY(option.rect.y());
            rect.setWidth(option.rect.width());
            rect.setHeight(option.rect.height());
            path.addRect(rect);
            DPalette pa = DPaletteHelper::instance()->palette(m_parentView);
            QColor fillColor = option.palette.color(cg, DPalette::Highlight);
            painter->fillPath(path, QBrush(fillColor));

            painter->setPen(QPen(option.palette.color(DPalette::HighlightedText)));

            QRect searchTextRect = QRect(rect.left() + 32, rect.top() + 7, rect.width() - 64, rect.height() - 14);
            QFontMetrics fontMetric(nameFont);
            const QString elidedSearchText = fontMetric.elidedText(searchText, Qt::ElideRight, rect.width() - 64);
            qCDebug(app) << "Original text:" << searchText
                        << "Elided text:" << elidedSearchText
                        << "Available width:" << rect.width() - 64;
            painter->drawText(searchTextRect, Qt::AlignLeft | Qt::AlignVCenter, elidedSearchText);
            qCDebug(app) << "Text drawn in selected state";
        } else {
            QPainterPath path;
            QRect rect;
            rect.setX(option.rect.x());
            rect.setY(option.rect.y() + 1);
            rect.setWidth(option.rect.width());
            rect.setHeight(option.rect.height() - 1);
            path.addRect(rect);
            DPalette pa = DPaletteHelper::instance()->palette(m_parentView);
            DStyleHelper styleHelper;
            QColor fillColor = styleHelper.getColor(static_cast<const QStyleOption *>(&option), pa, DPalette::ItemBackground);
            painter->fillPath(path, QBrush(fillColor));

            painter->setPen(QPen(option.palette.color(DPalette::ToolTipText)));

            QRect searchTextRect = QRect(rect.left() + 32, rect.top() + 6, rect.width() - 64, rect.height() - 13);
            QFontMetrics fontMetric(nameFont);
            const QString elidedSearchText = fontMetric.elidedText(searchText, Qt::ElideRight, rect.width() - 64);
            qCDebug(app) << "Original text:" << searchText
                        << "Elided text:" << elidedSearchText
                        << "Available width:" << rect.width() - 64;
            painter->drawText(searchTextRect, Qt::AlignLeft | Qt::AlignVCenter, elidedSearchText);
            qCDebug(app) << "Text drawn in normal state";
        }

        painter->restore();
    } else {
        DStyledItemDelegate::paint(painter, option, index);
    }
}

QSize SearchCompletionDelegate::sizeHint(const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    qCDebug(app) << "SearchCompletionDelegate::sizeHint() called for index:" << index;
    if (0 == index.row()) {
        qCDebug(app) << "Returning default size 41";
        return QSize(option.rect.width(), 34 + 7);
    } else {
        qCDebug(app) << "Returning default size 34";
        return QSize(option.rect.width(), 34);
    }
}
