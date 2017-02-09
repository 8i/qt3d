/****************************************************************************
**
** Copyright (C) 2017 Klaralvdalens Datakonsult AB (KDAB).
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
/****************************************************************************
**
** Copyright (C) 2017 Klaralvdalens Datakonsult AB (KDAB).
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

#include "qphysicsaspect.h"
#include "qphysicsaspect_p.h"

#include <Qt3DPhysics/qphysicsworld.h>
#include <Qt3DPhysics/qcollider.h>
#include <Qt3DPhysics/qphysicsmaterial.h>

#include <Qt3DPhysics/private/physicsworld_p.h>
#include <Qt3DPhysics/private/collider_p.h>
#include <Qt3DPhysics/private/physicsmaterial_p.h>

QT_BEGIN_NAMESPACE

using namespace Qt3DCore;

namespace Qt3DPhysics {

QPhysicsAspectPrivate::QPhysicsAspectPrivate()
    : QAbstractAspectPrivate()
{
}

/*!
    \class Qt3DInput::QInputAspect
    \inherits Qt3DCore::QAbstractAspect
    \inmodule Qt3DInput
    \brief Responsible for creating physical devices and handling associated jobs.
    \since 5.5
    \brief Handles mapping between front and backend nodes

    QInputAspect is responsible for creating physical devices.
    It is also the object responsible establishing the jobs to run at a particular time from the current input setup.
*/

/*!
 * Constructs a new QInputAspect with \a parent.
 */
QPhysicsAspect::QPhysicsAspect(QObject *parent)
    : QPhysicsAspect(*new QPhysicsAspectPrivate, parent)
{
}

/*! \internal */
QPhysicsAspect::QPhysicsAspect(QPhysicsAspectPrivate &dd, QObject *parent)
    : QAbstractAspect(dd, parent)
{
    setObjectName(QStringLiteral("Physics Aspect"));

    registerBackendType<QPhysicsWorld>(QBackendNodeMapperPtr(new Physics::PhysicsWorldFunctor(this)));
    registerBackendType<QCollider>(QBackendNodeMapperPtr(new Physics::ColliderFunctor(this)));
    registerBackendType<QPhysicsMaterial>(QBackendNodeMapperPtr(new Physics::PhysicsMaterialFunctor(this)));
}

/*! \internal */
QPhysicsAspect::~QPhysicsAspect()
{
}

/*!
    \internal
 */
QVector<QAspectJobPtr> QPhysicsAspect::jobsToExecute(qint64 time)
{
    Q_UNUSED(time);

    QVector<QAspectJobPtr> jobs;
    return jobs;
}

/*!
    \internal
 */
void QPhysicsAspect::onRegistered()
{
}

/*!
    \internal
 */
void QPhysicsAspect::onUnregistered()
{
}

} // namespace Qt3DPhysics

QT_END_NAMESPACE

QT3D_REGISTER_NAMESPACED_ASPECT("physics", QT_PREPEND_NAMESPACE(Qt3DPhysics), QPhysicsAspect)
