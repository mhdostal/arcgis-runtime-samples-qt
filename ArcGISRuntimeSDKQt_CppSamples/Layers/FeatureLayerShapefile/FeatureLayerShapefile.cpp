// [WriteFile Name=FeatureLayerShapefile, Category=Layers]
// [Legal]
// Copyright 2017 Esri.

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

#include "FeatureLayerShapefile.h"

#include "Map.h"
#include "MapQuickView.h"
#include "Basemap.h"
#include "ShapefileFeatureTable.h"
#include "FeatureLayer.h"

#include <QQmlProperty>


using namespace Esri::ArcGISRuntime;

FeatureLayerShapefile::FeatureLayerShapefile(QQuickItem* parent /* = nullptr */):
    QQuickItem(parent)
{
}

void FeatureLayerShapefile::init()
{
    // Register the map view for QML
    qmlRegisterType<MapQuickView>("Esri.Samples", 1, 0, "MapView");
    qmlRegisterType<FeatureLayerShapefile>("Esri.Samples", 1, 0, "FeatureLayerShapefileSample");
}

void FeatureLayerShapefile::componentComplete()
{
    QQuickItem::componentComplete();

    QString dataPath = QQmlProperty::read(this, "dataPath").toString();

    // find QML MapView component
    m_mapView = findChild<MapQuickView*>("mapView");

    // Create a map using the topographic basemap
     m_map = new Map(Basemap::streetsVector(this), this);

    // Set map to map view
    m_mapView->setMap(m_map);

    // Create and add the shapefile to the map
    createAndAddShapefileLayer(dataPath + "Public_Art.shp");
}
void FeatureLayerShapefile::createAndAddShapefileLayer(const QUrl& file)
{

    QString dataPath = file.toLocalFile();

    // Create the ShapefileFeatureTable
    ShapefileFeatureTable* featureTable = new ShapefileFeatureTable(dataPath, this);

    // Create the feature layer from the ShapefileFeatureTable
    FeatureLayer* layer = new FeatureLayer(featureTable, this);

    connect(layer, &FeatureLayer::doneLoading, this, [this, layer](Error loadError)
    {
        if (!loadError.isEmpty())
          return;

        // If the layer was loaded successfully, set the map extent to the full extent of the layer
        m_mapView->setViewpointCenter(layer->fullExtent().center(), 80000);
    });

    // Add the shapefile layer to the map
    m_map->operationalLayers()->clear();
    m_map->operationalLayers()->append(layer);
}
