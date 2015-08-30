/****************************************************************************
**
** Copyright (C) 2015 Klaralvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QT3DINPUT_INPUT_MOUSEINPUT_H
#define QT3DINPUT_INPUT_MOUSEINPUT_H

#include <Qt3DCore/qbackendnode.h>
#include <Qt3DInput/q3dmouseevent.h>

QT_BEGIN_NAMESPACE

namespace Qt3DInput {
namespace Input {

class InputHandler;

class MouseInput : public Qt3D::QBackendNode
{
public:
    MouseInput();
    ~MouseInput();

    void updateFromPeer(Qt3D::QNode *peer) Q_DECL_OVERRIDE;
    Qt3D::QNodeId mouseController() const;
    void setInputHandler(InputHandler *handler);
    void mouseEvent(const Q3DMouseEventPtr &event);
    void wheelEvent(const Q3DWheelEventPtr &event);

    inline bool isEnabled() const { return m_enabled; }

protected:
    void sceneChangeEvent(const Qt3D::QSceneChangePtr &e) Q_DECL_OVERRIDE;
    void setController(const Qt3D::QNodeId &controller);

private:
    bool m_enabled;
    Qt3D::QNodeId m_mouseController;
    InputHandler *m_inputHandler;
};

class MouseInputFunctor : public Qt3D::QBackendNodeFunctor
{
public:
    explicit MouseInputFunctor(InputHandler *handler);

    Qt3D::QBackendNode *create(Qt3D::QNode *frontend, const Qt3D::QBackendNodeFactory *factory) const Q_DECL_OVERRIDE;
    Qt3D::QBackendNode *get(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;
    void destroy(const Qt3D::QNodeId &id) const Q_DECL_OVERRIDE;

private:
    InputHandler *m_handler;
};

} // namespace Input
} // namespace Qt3DInput

QT_END_NAMESPACE

#endif // MOUSEINPUT_H
