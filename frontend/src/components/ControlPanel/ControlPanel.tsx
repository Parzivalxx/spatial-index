import React from 'react';
import GeneratePoints from './GeneratePoints';
import QuerySelector from './QuerySelector';

interface ControlPanelProps {
  onGeneratePoints: (numPoints: number) => void;
  onQueryTypeChange: (queryType: string) => void;
  onDataStructureChange: (dataStructure: string) => void;
  selectedDataStructure: string;
  selectedQueryType: string;
}

const ControlPanel: React.FC<ControlPanelProps> = ({
  onGeneratePoints,
  onQueryTypeChange,
  onDataStructureChange,
  selectedDataStructure,
  selectedQueryType,
}) => {
  return (
    <div>
      <GeneratePoints onGeneratePoints={onGeneratePoints} />
      <QuerySelector
        selectedDataStructure={selectedDataStructure}
        selectedQueryType={selectedQueryType}
        onDataStructureChange={onDataStructureChange}
        onQueryTypeChange={onQueryTypeChange}
      />
    </div>
  );
};

export default ControlPanel;
