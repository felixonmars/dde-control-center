#include "miracastmodel.h"

MiracastModel::MiracastModel(QObject *parent)
    : QObject(parent)
{

}

void MiracastModel::addPeer(const PeerInfo &peer)
{
    emit peerAdded(peer);
}

void MiracastModel::addLink(const LinkInfo &link)
{
    if (m_links.contains(link))
        return;

    m_links.append(link);

    emit linkAdded(link);
}

void MiracastModel::setLinks(const QList<LinkInfo> &links)
{
    for (const auto &link : links)
        addLink(link);
}

void MiracastModel::onPathAdded(const QDBusObjectPath &path, const QString &info)
{
    const QJsonObject infoObject = QJsonDocument::fromJson(info.toUtf8()).object();
    const QString objectPath = path.path();

    if (objectPath.startsWith("/org/freedesktop/miracle/wifi/link/"))
        return addLink(LinkInfo::fromJson(infoObject));
    else if (objectPath.startsWith("/org/freedesktop/miracle/wifi/peer/"))
        return addPeer(PeerInfo::fromJson(infoObject));

    qDebug() << path.path() << info;
}

void MiracastModel::onPathRemoved(const QDBusObjectPath &path)
{
    qDebug() << path.path();
}

void MiracastModel::onMiracastEvent(const uchar type, const QDBusObjectPath &path)
{
    qDebug() << type << path.path();

    switch (type)
    {
    case LinkManaged:
        linkByPath(path).m_managed = true;
        emit requestLinkScanning(path, true);
        break;
    case LinkUnmanaged:
        linkByPath(path).m_managed = false;
        break;
    default:;
    }
}

LinkInfo &MiracastModel::linkByPath(const QDBusObjectPath &path)
{
    for (auto it(m_links.begin()); it != m_links.end(); ++it)
        if (it->m_dbusPath == path)
            return *it;

    Q_UNREACHABLE();
}