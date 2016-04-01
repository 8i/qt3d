/****************************************************************************
**
** Copyright (C) 2015 Klaralvdalens Datakonsult AB (KDAB).
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QT3DRENDER_RENDER_TEXTUREIMAGE_H
#define QT3DRENDER_RENDER_TEXTUREIMAGE_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <Qt3DRender/private/backendnode_p.h>
#include <Qt3DRender/private/handle_types_p.h>
#include <Qt3DRender/qabstracttexture.h>
#include <Qt3DRender/qabstracttextureimage.h>
#include <qglobal.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {

namespace Render {

class TextureManager;
class TextureImageManager;
class TextureDataManager;

typedef uint TextureImageDNA;

class TextureImage : public BackendNode
{
public:
    TextureImage();
    void cleanup();
    void updateFromPeer(Qt3DCore::QNode *peer) Q_DECL_OVERRIDE;
    void sceneChangeEvent(const Qt3DCore::QSceneChangePtr &e) Q_DECL_OVERRIDE;

    int m_layer;
    int m_mipLevel;
    QAbstractTexture::CubeMapFace m_face;
    bool m_dirty;
    inline TextureImageDNA dna() const { return m_dna; }

    inline int layer() const { return m_layer; }
    inline int mipLevel() const { return m_mipLevel; }
    inline QAbstractTexture::CubeMapFace face() const { return m_face; }

    void setTextureManager(TextureManager *manager);
    void setTextureImageManager(TextureImageManager *manager);
    void setTextureDataManager(TextureDataManager *manager);
    void unsetDirty();

    inline bool isDirty() const { return m_dirty; }
    inline QTextureImageDataGeneratorPtr textureDataGenerator() const { return m_generator; }

    void setTextureDataHandle(HTextureData handle);

    inline HTextureData textureDataHandle() const { return m_textureDataHandle; }
    inline QTextureImageDataGeneratorPtr dataGenerator() const { return m_generator; }

private:
    void initializeFromPeer(const Qt3DCore::QNodeCreatedChangeBasePtr &change) Q_DECL_FINAL;

    void updateDNA();

    QTextureImageDataGeneratorPtr m_generator;
    HTextureData m_textureDataHandle;
    TextureManager *m_textureManager;
    TextureImageManager *m_textureImageManager;
    TextureDataManager *m_textureDataManager;
    QVector<Qt3DCore::QNodeId> m_referencedTextures;
    HTexture m_textureProvider;
    Qt3DCore::QNodeId m_textureProviderId;
    TextureImageDNA m_dna;
};

class TextureImageFunctor : public Qt3DCore::QBackendNodeMapper
{
public:
    explicit TextureImageFunctor(AbstractRenderer *renderer,
                                 TextureManager *textureManager,
                                 TextureImageManager *textureImageManager,
                                 TextureDataManager *textureDataManager);

    Qt3DCore::QBackendNode *create(Qt3DCore::QNode *frontend) const Q_DECL_FINAL;
    Qt3DCore::QBackendNode *create(const Qt3DCore::QNodeCreatedChangeBasePtr &change) const Q_DECL_FINAL;
    Qt3DCore::QBackendNode *get(Qt3DCore::QNodeId id) const Q_DECL_FINAL;
    void destroy(Qt3DCore::QNodeId id) const Q_DECL_FINAL;

private:
    TextureManager *m_textureManager;
    TextureImageManager *m_textureImageManager;
    TextureDataManager *m_textureDataManager;
    AbstractRenderer *m_renderer;
};


} // namespace Render

} // namespace Qt3DRender

QT_END_NAMESPACE

#endif // QT3DRENDER_RENDER_TEXTUREIMAGE_H
