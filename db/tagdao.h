#ifndef TAGDAO_H
#define TAGDAO_H

#include "basedao.h"

#include <QString>
#include <vector>
#include <QMap>
#include <model/tag.h>

using namespace std;
class TagDao : public BaseDao {
public:
    TagDao();

    void add(Tag *tag);
    Tag* get(uint id);
    Tag* getByName(QString name);
    vector<Tag> list(QString k);
    virtual uint getMaxId() const;
    void del(uint id);
    QMap<uint,uint> countTag(uint target);
    uint countTag(uint id, uint target);
    vector<uint> findTagIdByTag(QString tag);
    QString getTagCondByTags(QStringList tags);
};

#endif // TAGDAO_H
