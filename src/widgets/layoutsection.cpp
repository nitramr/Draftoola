
#include <QLayout>
#include <QPainter>
#include <QWidgetAction>
#include <QMenu>
#include <QDebug>
#include "layoutsection.h"
#include "popupmenu.h"


LayoutSectionHeader::LayoutSectionHeader( QString text, QWidget *menu, bool toggle, QWidget *parent ) : QWidget( parent ){
    QFont m_font(this->font());
    m_font.setBold( true );

    int limit = 24;
    m_collapsed = false; // Expanded by default


    // Caption
    m_caption = new QLabel();
    m_caption->setText( text );
    m_caption->setFont( m_font );


    // Menu Button
    m_btnMenu = new QToolButton();
    m_btnMenu->setFixedSize( limit,limit );
    m_btnMenu->setIcon( QIcon(":/icons/dark/settings.svg") );
    m_btnMenu->setToolButtonStyle( Qt::ToolButtonStyle::ToolButtonIconOnly );
    m_btnMenu->setAutoRaise( true );

    if( menu == nullptr ){
        m_btnMenu->hide();
    }else{
        PopupMenu * menuExtended = new PopupMenu( menu );
        m_btnMenu->setMenu( menuExtended );
        m_btnMenu->setStyleSheet( "QToolButton::menu-indicator { image: none; }" );
    }


    // Expand / Collapse Button
    m_btnCollapse = new QToolButton();
    m_btnCollapse->setFixedSize( limit,limit );
    m_btnCollapse->setIcon( QIcon(":/icons/dark/chevron-down.svg") );
    m_btnCollapse->setToolButtonStyle( Qt::ToolButtonStyle::ToolButtonIconOnly );
    m_btnCollapse->setAutoRaise( true );

    if( !toggle ){
        m_btnCollapse->hide();
    }

    // Layout
    m_headerLayout = new QHBoxLayout();
    m_headerLayout->addWidget( m_caption );
    m_headerLayout->addStretch( 0 );
    m_headerLayout->addWidget( m_btnMenu );
    m_headerLayout->addWidget( m_btnCollapse );
    m_headerLayout->setContentsMargins( 4,4,4,4 );
//    m_headerLayout->setSpacing( 0 );


    this->setLayout( m_headerLayout );
    this->setMinimumHeight( limit );
    this->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Maximum );

    this->connect( m_btnCollapse, &QToolButton::clicked,this, &LayoutSectionHeader::setCollapsedState );

}

void LayoutSectionHeader::paintEvent( QPaintEvent * ){

    QColor lineColor( this->palette().mid().color() ); //(128,128,128,128);
//    int lineWidth = 1;

    QPainter painter( this );
    painter.setPen( lineColor );
    painter.drawLine( 0,0,this->width(), 0 );
//    painter.drawLine( 0,this->height()-lineWidth,this->width(), this->height()-lineWidth );

}

void LayoutSectionHeader::setCollapsedState(){
    ( m_collapsed ) ? m_collapsed = false : m_collapsed = true;

    emit sendCollapsedState( m_collapsed );
}

void LayoutSectionHeader::setCollapsed( bool isCollapsed ){

    if(isCollapsed){
        m_btnCollapse->setIcon( QIcon(":/icons/dark/chevron-right.svg") );
    } else {
        m_btnCollapse->setIcon( QIcon(":/icons/dark/chevron-down.svg") );
    }

    m_collapsed = isCollapsed;

}

void LayoutSectionHeader::addButton( QToolButton *button ){
    button->setAutoRaise( true );
    button->setFixedSize( 24,24 );
    m_headerLayout->insertWidget( m_headerLayout->count() - 2, button );
}

void LayoutSectionHeader::removeButton( QToolButton *button ){
    m_headerLayout->removeWidget( button );
    button->deleteLater();
}


LayoutSection::LayoutSection(QString text, QWidget *menu, bool toggle, QWidget *parent) : QWidget(parent){

    QSizePolicy sizePol = QSizePolicy( QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::MinimumExpanding );

    m_flowLayout = new QVBoxLayout();
    m_flowLayout->setContentsMargins( 0,0,0,0 );
    m_header = new LayoutSectionHeader( text, menu, toggle );
    m_drawer = new QWidget();
    m_drawer->setLayout(m_flowLayout);
    m_drawer->setSizePolicy(sizePol);

    QVBoxLayout * m_mainLayout = new QVBoxLayout();
    m_mainLayout->setContentsMargins( 0,0,0,0 );
    m_mainLayout->setMargin( 0 );
    m_mainLayout->setSpacing(0);
    m_mainLayout->addWidget( m_header );
    m_mainLayout->addWidget( m_drawer );

    this->setSizePolicy( sizePol );
    this->setLayout( m_mainLayout );
    this->connect( m_header, &LayoutSectionHeader::sendCollapsedState, this, &LayoutSection::setCollapsedState );
}


void LayoutSection::addWidget(QWidget * item){

    m_flowLayout->addWidget(item);

}

void LayoutSection::addButton(QToolButton *button){
    m_header->addButton(button);
}

void LayoutSection::removeButton(QToolButton *button){
    m_header->removeButton(button);
}


void LayoutSection::setCollapsedState(bool state){
    m_header->setCollapsed(state);

    if( state ){
        m_drawer->hide();
        this->setMaximumHeight(m_header->height());
    } else {
        m_drawer->show();
        this->setMaximumHeight(QWIDGETSIZE_MAX);
    }
}
