// [WriteFile Name=FeatureLayerDefinitionExpression, Category=Features]
// [Legal]
// Copyright 2016 Esri.

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// [Legal]

#ifndef FEATURE_LAYER_DEFINITION_EXPRESSION_H
#define FEATURE_LAYER_DEFINITION_EXPRESSION_H

namespace Esri
{
    namespace ArcGISRuntime
    {
        class Map;
        class MapQuickView;
        class FeatureLayer;
    }
}

#include <QQuickItem>

class FeatureLayerDefinitionExpression : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(bool layerInitialized READ layerInitialized NOTIFY layerInitializedChanged)

public:
    FeatureLayerDefinitionExpression(QQuickItem* parent = 0);
    ~FeatureLayerDefinitionExpression();

    void componentComplete() Q_DECL_OVERRIDE;
    Q_INVOKABLE void setDefExpression(QString whereClause);

signals:
    void layerInitializedChanged();

private:
    bool layerInitialized() const;

private:
    Esri::ArcGISRuntime::Map* m_map;
    Esri::ArcGISRuntime::MapQuickView* m_mapView;
    Esri::ArcGISRuntime::FeatureLayer* m_featureLayer;
    bool m_initialized;
};

#endif // FEATURE_LAYER_DEFINITION_EXPRESSION_H

