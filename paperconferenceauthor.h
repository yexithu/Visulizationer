#ifndef PAPERCONFERENCEAUTHOR_H
#define PAPERCONFERENCEAUTHOR_H

#include "stdafx.h"
#include "nodebase.h"
#include "graphbase.h"
#include "edgebase.h"
#include <vector>
#include <QHash>
#include <QString>
#include <QDir>
#include <QFile>
#include <QColor>
#include <vtkSmartPointer.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkGraphLayout.h>
#include <vtkCircularLayoutStrategy.h>
#include <vtkForceDirectedLayoutStrategy.h>
#include <vtkFast2DLayoutStrategy.h>
class AcademicNode:public NodeBase
{
public:
    enum Type;
    AcademicNode(int nodeIndex, int nodeId, Type type, int myear, 
        QColor viewColor, QString academicId, QString viewLable, double viewLayout[3]);
    ~AcademicNode();
    friend class PaperConferenceAuthorGraph;

    static QColor GetViewColor(const QString &origin);
    static void GetViewLayout(double * viewLayout, const QString &origin);
private:

protected:
    enum Type
    {
        Paper,
        Conference,
        Author
    };
    Type mType;
    int mYear;
    QColor mViewColor;
    QString mViewLable;
    QString mAcademicId;
    double* mViewLayout;
    
};

class PaperNode :public AcademicNode
{
public:
    PaperNode(int nodeIndex, int nodeId, Type type, int myear,
        QColor viewColor, QString academicId, QString viewLable, double viewLayout[3]);
    ~PaperNode();
    friend class PaperConferenceAuthorGraph;
private:
    QString mAuthors;
    int mDataFrom;
    int mPageFrom;
    QString mPaperTitle;
    QString mPaperTitleShort;
};
class ConferenceNode :public AcademicNode
{
public:
    ConferenceNode(int nodeIndex, int nodeId, Type type, int myear,
        QColor viewColor, QString academicId, QString viewLable, double viewLayout[3]);
    ~ConferenceNode();
    friend class PaperConferenceAuthorGraph;
private:
    QString mConferenceName;
    QString mConferenceNameShort;
};

class AuthorNode : public AcademicNode
{
public:
    AuthorNode(int nodeIndex, int nodeId, Type type, int myear,
        QColor viewColor, QString academicId, QString viewLable, double viewLayout[3]);
    ~AuthorNode();
    friend class PaperConferenceAuthorGraph;
private:
    QString mAuthorName;
    QString mAuthorNameShort;
};

class DirectedEdge : public EdgeBase
{
public:
    DirectedEdge();
    ~DirectedEdge();
    friend class PaperConferenceAuthorGraph;
private:
};



class PaperConferenceAuthorGraph : public GraphBase
{
public:
    PaperConferenceAuthorGraph(QObject *parent = 0);
    ~PaperConferenceAuthorGraph();

public:
    QHash<int, int> mNodeIdHashIndex;
    vector<AcademicNode *> tea;
    void SetTestPos();
    
private:

    void LoadNodes(QString nodeInFileName);
    void LoadEdges(QString edgeInFileName);
protected:
    virtual void ConstructScene();
};

#endif