import React, { useRef, useEffect, useState, Dispatch, SetStateAction } from 'react';
import { createOrPopulateChart } from './functions/createOrPopulateChart';
import * as d3 from 'd3';
import { Point } from '../../types/Point';
import { performRangeQuery } from './functions/performRangeQuery';
import { performKnnQuery } from './functions/performKnnQuery';
import './Chart.css';

interface ChartProps {
  points: Point[];
  queriedPoints: Point[];
  setQueriedPoints: Dispatch<SetStateAction<never[]>>;
  dataStructure: string;
  queryType: string;
  numNearestNeighbours: number;
  setQueryTime: Dispatch<SetStateAction<number>>;
}

const Chart: React.FC<ChartProps> = ({
  points,
  queriedPoints,
  setQueriedPoints,
  dataStructure,
  queryType,
  numNearestNeighbours,
  setQueryTime,
}) => {
  const chartRef = useRef(null);
  const chartInstance = useRef(null);
  const [isSelecting, setIsSelecting] = useState(false);
  const [selectionRect, setSelectionRect] = useState({
    startX: 0,
    startY: 0,
    endX: 0,
    endY: 0,
  });
  const [clickedX, setClickedX] = useState(0);
  const [clickedY, setClickedY] = useState(0);

  const [chartDimensions, setChartDimensions] = useState({
    size: Math.min(window.innerWidth, window.innerHeight) * 0.8, // Adjust as needed
  });

  const xScale = d3.scaleLinear().domain([0, 100]).range([0, chartDimensions.size]);
  const yScale = d3.scaleLinear().domain([0, 100]).range([chartDimensions.size, 0]);

  useEffect(() => {
    const handleResize = () => {
      setChartDimensions({
        size: Math.min(window.innerWidth, window.innerHeight) * 0.8,
      });
    };

    window.addEventListener('resize', handleResize);

    return () => {
      window.removeEventListener('resize', handleResize);
    };
  }, []);

  useEffect(() => {
    const cleanUp = createOrPopulateChart(
      chartRef,
      chartInstance,
      points,
      chartDimensions.size,
      chartDimensions.size,
      queriedPoints,
      xScale,
      yScale,
      setIsSelecting,
      setSelectionRect,
      queryType,
      setClickedX,
      setClickedY,
    );
    return () => {
      if (cleanUp) {
        cleanUp();
      }
    };
  }, [dataStructure, queryType, points, queriedPoints]);

  useEffect(() => {
    if (isSelecting) {
      return;
    }
    performRangeQuery(selectionRect, dataStructure, setQueriedPoints, setQueryTime);
  }, [isSelecting]);

  useEffect(() => {
    performKnnQuery(clickedX, clickedY, dataStructure, numNearestNeighbours, setQueriedPoints, setQueryTime);
  }, [clickedX, clickedY]);

  return <div ref={chartRef} className="chart-container"></div>;
};

export default Chart;
