#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>

#include "ContextModel.h"

namespace bb
{
    namespace cascades
    {
        class Application;
        class LocaleHandler;
    }
}

class QTranslator;


class TDList : public QObject
{
    Q_OBJECT
public:
    TDList(bb::cascades::Application *app);
    virtual ~TDList() { }

private slots:

private:

private:
	ContextModel* mainModel;
};

#endif /* ApplicationUI_HPP_ */
