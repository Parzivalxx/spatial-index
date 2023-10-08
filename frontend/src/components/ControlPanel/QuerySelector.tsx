import React from 'react';

interface QuerySelectorProps {
  selectedDataStructure: string;
  selectedQueryType: string;
  onDataStructureChange: (dataStructure: string) => void;
  onQueryTypeChange: (queryType: string) => void;
}

const QuerySelector: React.FC<QuerySelectorProps> = ({
  selectedDataStructure,
  selectedQueryType,
  onDataStructureChange,
  onQueryTypeChange,
}) => {
  return (
    <div>
      <div>
        <label>Data Structure:</label>
        <select value={selectedDataStructure} onChange={(e) => onDataStructureChange(e.target.value)}>
          <option value="quadtree">Quad Tree</option>
          <option value="kdtree">KD-Tree</option>
          <option value="bruteforce">Brute Force</option>
        </select>
      </div>
      <div>
        <label>Query Type:</label>
        <select value={selectedQueryType} onChange={(e) => onQueryTypeChange(e.target.value)}>
          <option value="range">Range Query</option>
          <option value="knn">KNN Query</option>
        </select>
      </div>
    </div>
  );
};

export default QuerySelector;
