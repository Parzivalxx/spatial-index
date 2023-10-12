import React from 'react';
import GeneratePoints from './GeneratePoints';
import QuerySelector from './QuerySelector';

interface ControlPanelProps {
  onGeneratePoints: (numPoints: number) => void;
  onQueryTypeChange: (queryType: string) => void;
  onDataStructureChange: (dataStructure: string) => void;
  selectedDataStructure: string;
  selectedQueryType: string;
  numNearestNeighbours: number;
  onNumNearestNeighboursChange: (num: number) => void;
  queryTime: number;
}

const ControlPanel: React.FC<ControlPanelProps> = ({
  onGeneratePoints,
  onQueryTypeChange,
  onDataStructureChange,
  selectedDataStructure,
  selectedQueryType,
  numNearestNeighbours,
  onNumNearestNeighboursChange,
  queryTime,
}) => {
  return (
    <div className="mt-5">
      <GeneratePoints onGeneratePoints={onGeneratePoints} />
      <QuerySelector
        selectedDataStructure={selectedDataStructure}
        selectedQueryType={selectedQueryType}
        onDataStructureChange={onDataStructureChange}
        onQueryTypeChange={onQueryTypeChange}
        numNearestNeighbours={numNearestNeighbours}
        onNumNearestNeighboursChange={onNumNearestNeighboursChange}
        queryTime={queryTime}
      />
    </div>
  );
};

export default ControlPanel;
